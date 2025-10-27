#include "Player.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

Player::Player(std::string nume) : nume(nume), pokemon(nullptr) {}

Player::~Player() {
    if (pokemon)
        delete pokemon;
}


void Player::alegePokemon(std::vector<Pokemon*>& listaPokemoni, bool eAI) {
    std::cout << "\n" << nume << ", alege-ti Pokemonul!\n";
    for (size_t i = 0; i < listaPokemoni.size(); i++) {
        std::cout << i + 1 << ". ";
        listaPokemoni[i]->afiseazaInfo();
    }


    int alegere;
    if (eAI) {
        alegere = rand() % listaPokemoni.size();
        std::cout << nume << " (AI) a ales " << listaPokemoni[alegere]->getNume() << "!\n";
    } else {
        std::cout << "Introdu numarul Pokemonului ales: ";
        std::cin >> alegere;
        alegere--;
    }
    pokemon = new Pokemon(*listaPokemoni[alegere]);
}

Pokemon* Player::getPokemon() const { return pokemon; }
std::string Player::getNume() const { return nume; }