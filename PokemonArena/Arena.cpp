#include "Arena.h"
#include <random>
#include <fstream>

Arena::Arena() {

    listaPokemoni.push_back(new Pokemon("Pikachu", "Electric", 1200, 55, 40, 90));
    listaPokemoni.push_back(new Pokemon("Bulbasaur", "Iarba",   1400, 49, 49, 45));
    listaPokemoni.push_back(new Pokemon("Charmander", "Foc",    1200, 52, 43, 65));
    listaPokemoni.push_back(new Pokemon("Squirtle", "Apa",      1300, 48, 65, 43));
}

Arena::~Arena() {
    for (auto p : listaPokemoni) delete p;

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

    fout << p1.getNume() << " " << p1.getPokemon()->getNume() << " "
         << p1.getPokemon()->getHP() << "\n";
    fout << p2.getNume() << " " << p2.getPokemon()->getNume() << " "
         << p2.getPokemon()->getHP() << "\n";

    fout.close();
}

void Arena::startGame() const {
    std::cout << "=== Pokemon Arena ===\n";
    std::cout << "1. Continuă ultimul meci\n";
    std::cout << "2. Joc nou\n";
    std::cout << "3. Afiseaza leaderboard-ul\n";
    std::cout << "Alege optiunea: ";

    int opt;
    std::cin >> opt;

    if (opt == 1) {
        std::ifstream fin("save.txt");
        if (!fin.is_open()) {
            std::cout << "Nu există un fisier de salvare.\n";
        } else {
            std::string nume1, poke1, nume2, poke2;
            int hp1, hp2;
            fin >> nume1 >> poke1 >> hp1;
            fin >> nume2 >> poke2 >> hp2;

            Player p1(nume1);
            Player p2(nume2);

            Pokemon* pk1 = nullptr;
            Pokemon* pk2 = nullptr;

            for (auto* p : listaPokemoni) {
                if (p->getNume() == poke1) pk1 = new Pokemon(*p);
                if (p->getNume() == poke2) pk2 = new Pokemon(*p);
            }

            if (pk1 && pk2) {
                pk1->primesteDamage(pk1->getHP() - hp1);
                pk2->primesteDamage(pk2->getHP() - hp2);

                p1.setPokemon(pk1);
                p2.setPokemon(pk2);

                std::cout << "\n=== Joc incarcat cu succes! ===\n";
                std::cout << *pk1 << "\n" << *pk2 << "\n";

                desfasoaraLupta(p1, p2);
                return;
            } else {
                std::cout << "Eroare: Pokemonii salvati nu au fost gasiti.\n";
            }
        }
    }
    else if (opt == 2) {
        std::cout << "=== Pokemon Arena ===\n";
        std::cout << "1. Player vs Player\n";
        std::cout << "2. Player vs AI\n";
        std::cout << "Alege modul: ";

        int mod;
        std::cin >> mod;
        std::string numeP1, numeP2;
        std::cout << "Introdu numele pentru Player 1: ";
        std::cin >> numeP1;
        if (mod == 1) {
            std::cout << "Introdu numele pentru Player 2: ";
            std::cin >> numeP2;
        } else {
            numeP2 = "AI";
        }
        Player p1(numeP1);
        Player p2(numeP2);

        p1.alegePokemon(listaPokemoni, false);
        p2.alegePokemon(listaPokemoni, mod == 2);

        const Pokemon* poke1 = p1.getPokemon();
        const Pokemon* poke2 = p2.getPokemon();

        std::cout << "\n=== Lupta incepe! ===\n";
        std::cout << p1 << " vs " << p2 << "\n";
        std::cout << *poke1 << "\n";
        std::cout << *poke2 << "\n";

        desfasoaraLupta(p1, p2);

    } else if (opt == 3) {
        afiseazaLeaderboard();
    }


}

void Arena::desfasoaraLupta(Player& p1, Player& p2) {
    const Pokemon* poke1 = p1.getPokemon();
    const Pokemon* poke2 = p2.getPokemon();

    Player* first;
    Player* second;

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distrib(1, 3);

    if (poke1->getSpeed() > poke2->getSpeed()) {
        first = &p1; second = &p2;
    } else if (poke1->getSpeed() < poke2->getSpeed()) {
        first = &p2; second = &p1;
    } else {
        if (std::uniform_int_distribution<>(0, 1)(gen) == 0) { first = &p1; second = &p2; }
        else { first = &p2; second = &p1; }
    }

    std::cout << first->getNume() << " va incepe primul!\n";

    while (poke1->esteViu() && poke2->esteViu()) {

        Pokemon* attacker = first->getPokemon();
        Pokemon* defender = second->getPokemon();

        std::cout << "\n" << first->getNume() << ", alege o actiune:\n";
        std::cout << "1. Atac normal\n";
        std::cout << "2. Aparare\n";
        std::cout << "3. Abilitate speciala\n> ";

        int actiune;
        if (first->getNume() == "AI") {
            actiune = distrib(gen);
        } else {
            std::cin >> actiune;
        }

        if (actiune == 1) {
            attacker->ataca(defender);
        } else if (actiune == 2) {
            attacker->setDefending(true);
            std::cout << attacker->getNume() << " se apara!\n";
        } else if (actiune == 3) {
            attacker->folosesteAbilitate(defender);
        } else {
            std::cout << "Actiune invalida. Se considera atac normal.\n";
            attacker->ataca(defender);
        }


        //if (poke1->esteViu() && poke2->esteViu())
        //{
        attacker = second->getPokemon();
        defender = first->getPokemon();

        std::cout << "\n" << second->getNume() << ", alege o actiune:\n";
        std::cout << "1. Atac normal\n";
        std::cout << "2. Aparare\n";
        std::cout << "3. Abilitate speciala\n> ";

        if (second->getNume() == "AI") {
            actiune = distrib(gen);
            std::cout << actiune << "\n";
        } else {
            std::cin >> actiune;
        }

        if (actiune == 1) {
            attacker->ataca(defender);
        } else if (actiune == 2) {
            attacker->setDefending(true);
            std::cout << attacker->getNume() << " se apara!\n";
        } else if (actiune == 3) {
            attacker->folosesteAbilitate(defender);
        } else {
            std::cout << "Actiune invalida. Se considera atac normal.\n";
            attacker->ataca(defender);
        }
        //}

        std::cout << "\n=== Stare dupa runda ===\n";
        std::cout << p1.getNume() << ": " << p1.getPokemon()->getHP() << " HP\n";
        std::cout << p2.getNume() << ": " << p2.getPokemon()->getHP() << " HP\n";

        p1.getPokemon()->reduceCooldown();
        p2.getPokemon()->reduceCooldown();

        salveazaProgres(p1, p2);

    }
    std::string castigator;
    if (poke1->esteViu()){
        std::cout << p1.getNume() << " a castigat!\n";
        castigator = p1.getNume();
    }
    else{
        std::cout << p2.getNume() << " a castigat!\n";
        castigator = p2.getNume();
    }
    actualizeazaLeaderboard(castigator);

    std::remove("save.txt");

}

std::ostream& operator<<(std::ostream& os, const Arena& a) {
    os << "Arena cu " << a.listaPokemoni.size() << " pokemoni disponibili.\n";
    return os;
}
