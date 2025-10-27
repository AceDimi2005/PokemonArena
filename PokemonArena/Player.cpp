#include "Player.h"
#include <iostream>
#include <utility>
#include <random>

Player::Player(std::string nume) : nume(std::move(nume)), pokemon(nullptr) {}

Player::~Player() {

        delete pokemon;
}


void Player::alegePokemon(const std::vector<Pokemon*>& listaPokemoni, bool eAI) {
    std::cout << "\n" << nume << ", alege-ti Pokemonul!\n";
    for (size_t i = 0; i < listaPokemoni.size(); i++) {
        std::cout << i + 1 << ". ";
        listaPokemoni[i]->afiseazaInfo();
    }


    int alegere;
    if (eAI) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, static_cast<int>(listaPokemoni.size()) - 1);
        alegere = distrib(gen);
        std::cout << nume << " (AI) a ales " << listaPokemoni[alegere]->getNume() << "!\n";
    } else {
        std::cout << "Introdu numarul Pokemonului ales: ";
        std::cin >> alegere;
        alegere--;
    }
    pokemon = new Pokemon(*listaPokemoni[alegere]);
}

Pokemon* Player::getPokemon() const { return pokemon; }
const std::string& Player::getNume() const { return nume; }