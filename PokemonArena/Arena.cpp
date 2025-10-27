#include "Arena.h"
#include <random>
#include <cmath>

Arena::Arena() {

    listaPokemoni.push_back(new Pokemon("Pikachu", "Electric", 120, 55, 40, 90));
    listaPokemoni.push_back(new Pokemon("Bulbasaur", "Iarba",   140, 49, 49, 45));
    listaPokemoni.push_back(new Pokemon("Charmander", "Foc",    120, 52, 43, 65));
    listaPokemoni.push_back(new Pokemon("Squirtle", "Apa",      130, 48, 65, 43));
}

Arena::~Arena() {
    for (auto p : listaPokemoni) delete p;

}

void Arena::startGame() const {
    std::random_device rd;
    std::cout << "=== Pokemon Arena ===\n";
    std::cout << "1. Player vs Player\n";
    std::cout << "2. Player vs AI\n";
    std::cout << "Alege modul: ";

    int mod;
    std::cin >> mod;

    Player p1("Player 1");
    Player p2(mod == 1 ? "Player 2" : "AI");

    p1.alegePokemon(listaPokemoni, false);
    p2.alegePokemon(listaPokemoni, mod == 2);

    Pokemon* poke1 = p1.getPokemon();
    Pokemon* poke2 = p2.getPokemon();

    std::cout << "\n=== Lupta incepe! ===\n";
    poke1->afiseazaInfo();
    poke2->afiseazaInfo();

    desfasoaraLupta(p1, p2);

}

void Arena::desfasoaraLupta(Player& p1, Player& p2) {
   Pokemon* poke1 = p1.getPokemon();
    Pokemon* poke2 = p2.getPokemon();

    Player* first;
    Player* second;

    std::random_device rd;
    std::mt19937 gen(rd());
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
        {
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
                int baseDamage = attacker->getAttack();
                if (baseDamage < 0) baseDamage = 0;
                int damage = static_cast<int>(std::round(baseDamage * 1.5));
                std::cout << attacker->getNume() << " foloseste o abilitate speciala si provoaca "
                          << damage << " damage!\n";
                defender->primesteDamage(damage);
            } else {
                std::cout << "Actiune invalida. Se considera atac normal.\n";
                attacker->ataca(defender);
            }
        }

        if (!poke1->esteViu() || !poke2->esteViu()) break;

        {
            Pokemon* attacker = second->getPokemon();
            Pokemon* defender = first->getPokemon();

            std::cout << "\n" << second->getNume() << ", alege o actiune:\n";
            std::cout << "1. Atac normal\n";
            std::cout << "2. Aparare\n";
            std::cout << "3. Abilitate speciala\n> ";

            int actiune = 1;
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
                int baseDamage = attacker->getAttack() - defender->getDefense()/2;
                if (baseDamage < 0) baseDamage = 0;
                int damage = static_cast<int>(std::round(baseDamage * 1.5));
                std::cout << attacker->getNume() << " foloseste o abilitate speciala si provoaca "
                          << damage << " damage!\n";
                defender->primesteDamage(damage);
            } else {
                std::cout << "Actiune invalida. Se considera atac normal.\n";
                attacker->ataca(defender);
            }
        }

        std::cout << "\n=== Stare dupa runda ===\n";
        std::cout << p1.getNume() << ": " << p1.getPokemon()->getHP() << " HP\n";
        std::cout << p2.getNume() << ": " << p2.getPokemon()->getHP() << " HP\n";


    }
    if (poke1->esteViu())
        std::cout << p1.getNume() << " a câștigat!\n";
    else
        std::cout << p2.getNume() << " a câștigat!\n";
}

std::ostream& operator<<(std::ostream& os, const Arena& a) {
    os << "Arena cu " << a.listaPokemoni.size() << " pokemoni disponibili.";
    return os;
}
