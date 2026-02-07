#include "../headers/Arena.h"
#include "../headers/GameException.h"
#include "../headers/GameConfig.h"
#include <iostream>
#include <fstream>
#include <random>
#include <locale>
#include <string>

static std::string formatMessage(std::string msg, const std::string& key, const std::string& value) {
    size_t pos;
    while ((pos = msg.find(key)) != std::string::npos) {
        msg.replace(pos, key.length(), value);
    }
    return msg;
}

Arena::Arena() : listaPokemoni(GameConfig::getInstance().getPokemons()) {
}

void Arena::afiseazaLeaderboard() {
    std::ifstream fin("leaderboard.txt");
    if (!fin.is_open()) {
        std::cout << "Nu exista leaderboard inca.\n";
        return;
    }

    std::cout << "\n=== LEADERBOARD ===\n";
    std::string n;
    int s;
    while (fin >> n >> s)
        std::cout << n << " — " << s << " victorii\n";

    std::cout << "==========================\n";
    fin.close();
}

void Arena::actualizeazaLeaderboard(const std::string& castigator) {
    std::ifstream fin("leaderboard.txt");
    std::vector<std::string> nume;
    std::vector<int> scoruri;

    std::string n;
    int s;
    bool gasit = false;

    while (fin >> n >> s) {
        if (n == castigator) {
            s++;
            gasit = true;
        }
        nume.push_back(n);
        scoruri.push_back(s);
    }
    fin.close();

    if (!gasit) {
        nume.push_back(castigator);
        scoruri.push_back(1);
    }

    std::ofstream fout("leaderboard.txt");
    for (size_t i = 0; i < nume.size(); i++) {
        fout << nume[i] << " " << scoruri[i] << "\n";
    }
    fout.close();

    std::cout << "Leaderboard actualizat!\n";
}

void Arena::salveazaProgres(const Player& p1, const Player& p2){
    std::ofstream fout("save.txt");
    if (!fout.is_open()) {
        std::cout << "Eroare: nu pot salva progresul.\n";
        return;
    }

    fout << p1.getNume() << " " << p1.getPokemon().getNume() << " "
         << p1.getPokemon().getHP() << "\n";
    fout << p2.getNume() << " " << p2.getPokemon().getNume() << " "
         << p2.getPokemon().getHP() << "\n";

    fout.close();
}

void Arena::startGame() const {
    std::cout << GameConfig::getInstance().getMessage("start_game_title");
    std::cout << GameConfig::getInstance().getMessage("menu_options");

    int opt;
    std::cin >> opt;

    if (opt == 1) {
        std::ifstream fin("save.txt");
        if (!fin.is_open()) {
            std::cout << GameConfig::getInstance().getMessage("save_file_missing");
        } else {
            std::string nume1, poke1, nume2, poke2;
            int hp1, hp2;
            fin >> nume1 >> poke1 >> hp1;
            fin >> nume2 >> poke2 >> hp2;

            Player p1(nume1);
            Player p2(nume2);

            Pokemon pk1, pk2;
            bool found1 = false, found2 = false;

            for (const auto& p : listaPokemoni) {
                if (p.getNume() == poke1) {
                    pk1 = p;
                    found1 = true;
                }
                if (p.getNume() == poke2) {
                    pk2 = p;
                    found2 = true;
                }
            }

            if (found1 && found2) {
                pk1.primesteDamage(pk1.getHP() - hp1);
                pk2.primesteDamage(pk2.getHP() - hp2);

                p1.setPokemon(pk1);
                p2.setPokemon(pk2);

                std::cout << GameConfig::getInstance().getMessage("game_load_success");
                std::cout << pk1 << "\n" << pk2 << "\n";

                desfasoaraLupta(p1, p2);
                return;
            } else {
                std::cout << GameConfig::getInstance().getMessage("game_load_fail");
            }
        }
    }
    else if (opt == 2) {
        std::cout << GameConfig::getInstance().getMessage("choose_mode_msg");

        int mod;
        std::cin >> mod;
        std::string numeP1, numeP2;

        std::cout << GameConfig::getInstance().getMessage("enter_name_p1");
        std::cin >> numeP1;

        if (mod == 1) {
            std::cout << GameConfig::getInstance().getMessage("enter_name_p2");
            std::cin >> numeP2;
        } else {
            numeP2 = "AI";
        }
        Player p1(numeP1);
        Player p2(numeP2);

        p1.alegePokemon(listaPokemoni, false);
        p2.alegePokemon(listaPokemoni, mod == 2);

        try {
            p1.getPokemon().valideaza();
            p2.getPokemon().valideaza();
        } catch (const GameException& e) {
            std::cout << "Eroare joc: " << e.what() << "\n";
            return;
        }

        std::cout << GameConfig::getInstance().getMessage("battle_start");
        std::cout << p1 << "\n" << p2 << "\n";

        desfasoaraLupta(p1, p2);

    } else if (opt == 3) {
        afiseazaLeaderboard();
    }
}

void Arena::desfasoaraLupta(Player& p1, Player& p2) const {
    setlocale(LC_ALL, "");

    Pokemon& poke1 = p1.getPokemon();
    Pokemon& poke2 = p2.getPokemon();

    Player* first;
    Player* second;

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distrib(1, 3);

    if (poke1.getSpeed() > poke2.getSpeed()) {
        first = &p1; second = &p2;
    } else if (poke1.getSpeed() < poke2.getSpeed()) {
        first = &p2; second = &p1;
    } else {
        if (std::uniform_int_distribution<>(0, 1)(gen) == 0) { first = &p1; second = &p2; }
        else { first = &p2; second = &p1; }
    }

    std::string msg = GameConfig::getInstance().getMessage("first_turn");
    msg = formatMessage(msg, "{name}", first->getNume());
    std::cout << msg;

   while (poke1.esteViu() && poke2.esteViu()) {
        Player* currentPlayers[] = {first, second};

        for (int i = 0; i < 2; ++i) {
            Player* active = currentPlayers[i];
            Player* inactive = (i == 0) ? second : first;
            Pokemon& attacker = active->getPokemon();
            Pokemon& defender = inactive->getPokemon();

            if (!attacker.esteViu()) continue;

            if (attacker.isStunned()) {
                std::string stunMsg = GameConfig::getInstance().getMessage("stunned_msg");
                stunMsg = formatMessage(stunMsg, "{name}", attacker.getNume());
                std::cout << stunMsg;
                attacker.setStunned(false);
            }
            else {
                std::string menuMsg = GameConfig::getInstance().getMessage("battle_action_menu");
                menuMsg = formatMessage(menuMsg, "{name}", active->getNume());
                std::cout << menuMsg;

                int actiune;
                if (active->getNume() == "AI") {
                    actiune = distrib(gen);
                } else {
                    std::cin >> actiune;
                }

                if (actiune == 1) {
                    int dmg = attacker.ataca(defender);
                    actionHistory.add(active->getNume() + " a atacat normal.");
                    damageHistory.add(dmg);
                } else if (actiune == 2) {
                    attacker.setDefending(true);
                    std::cout << attacker.getNume() << " a ales sa se apare.\n";
                    actionHistory.add(active->getNume() + " s-a aparat.");
                } else if (actiune == 3) {
                    attacker.folosesteAbilitate(defender);
                    actionHistory.add(active->getNume() + " a folosit abilitatea.");
                } else {
                    std::cout << GameConfig::getInstance().getMessage("invalid_action");
                    int dmg = attacker.ataca(defender);
                    damageHistory.add(dmg);
                }
            }
            if (!defender.esteViu()) break;
        }

        p1.getPokemon().reduceCooldown();
        p2.getPokemon().reduceCooldown();

        std::cout << "\n----------------------------------------\n";
        std::cout << "STATUS:\n";
        std::cout << p1.getNume() << " [" << p1.getPokemon().getNume() << "]: "
                  << p1.getPokemon().getHP() << " HP\n";

        std::cout << p2.getNume() << " [" << p2.getPokemon().getNume() << "]: "
                  << p2.getPokemon().getHP() << " HP\n";
        std::cout << "----------------------------------------\n";

        salveazaProgres(p1, p2);
    }

    std::string castigator = poke1.esteViu() ? p1.getNume() : p2.getNume();

    std::string winMsg = GameConfig::getInstance().getMessage("win_msg");
    winMsg = formatMessage(winMsg, "{name}", castigator);
    std::cout << winMsg;

    actionHistory.showAll("Istoric Actiuni Lupta");
    std::cout << "Total damage provocat in aceasta sesiune: " << damageHistory.getTotalValue() << "\n";

    actualizeazaLeaderboard(castigator);
    std::remove("save.txt");
}

std::ostream& operator<<(std::ostream& out, const Arena& a) {
    out << "=== Pokemon Arena ===\n";
    out << "Numar total de pokemoni disponibili: " << a.listaPokemoni.size() << "\n";
    out << "Lista pokemoni:\n";
    for (const auto& p : a.listaPokemoni) {
         out << p << "\n";
    }
    out << "=========================\n";
    return out;
}