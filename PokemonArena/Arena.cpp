#include "Arena.h"
#include <random>
#include <cmath>

Arena::Arena() {

    listaPokemoni.push_back(new Pokemon("Pikachu", "Electric", 1200, 55, 40, 90));
    listaPokemoni.push_back(new Pokemon("Bulbasaur", "Iarba",   1400, 49, 49, 45));
    listaPokemoni.push_back(new Pokemon("Charmander", "Foc",    1200, 52, 43, 65));
    listaPokemoni.push_back(new Pokemon("Squirtle", "Apa",      1300, 48, 65, 43));
}

Arena::~Arena() {
    for (auto p : listaPokemoni) delete p;

}

void Arena::startGame() const {
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

    const Pokemon* poke1 = p1.getPokemon();
    const Pokemon* poke2 = p2.getPokemon();

    std::cout << "\n=== Lupta incepe! ===\n";
    std::cout << *poke1 << "\n";
    std::cout << *poke2 << "\n";

    desfasoaraLupta(p1, p2);

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
                attacker->folosesteAbilitate(defender);
            } else {
                std::cout << "Actiune invalida. Se considera atac normal.\n";
                attacker->ataca(defender);
            }
        }

        //if (poke1->esteViu() && poke2->esteViu())
        //{
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
                attacker->folosesteAbilitate(defender);
            } else {
                std::cout << "Actiune invalida. Se considera atac normal.\n";
                attacker->ataca(defender);
            }
        //}

        std::cout << "\n=== Stare dupa runda ===\n";
        std::cout << p1.getNume() << ": " << p1.getPokemon()->getHP() << " HP\n";
        std::cout << p2.getNume() << ": " << p2.getPokemon()->getHP() << " HP\n";


    }
    p1.getPokemon()->reduceCooldown();
    p2.getPokemon()->reduceCooldown();

    if (poke1->esteViu())
        std::cout << p1.getNume() << " a câștigat!\n";
    else
        std::cout << p2.getNume() << " a câștigat!\n";
}

std::ostream& operator<<(std::ostream& os, const Arena& a) {
    os << "Arena cu " << a.listaPokemoni.size() << " pokemoni disponibili.";
    return os;
}
