#include "../headers/Player.h"
#include <iostream>
#include <utility>
#include <random>

Player::Player(std::string nume) : nume(std::move(nume)), pokemon("", "", 0, 0, 0, 0) {}

void Player::setPokemon(const Pokemon& pk) {
    pokemon = pk;
}

void Player::alegePokemon(const std::vector<Pokemon>& listaPokemoni, bool eAI) {
    std::cout << "\n" << nume << ", alege-ti Pokemonul!\n";
    for (size_t i = 0; i < listaPokemoni.size(); i++) {
        std::cout << i + 1 << ". ";
        std::cout << listaPokemoni[i] << "\n";
    }

    int alegere;
    if (eAI) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, static_cast<int>(listaPokemoni.size()) - 1);
        alegere = distrib(gen);
        std::cout << nume << " (AI) a ales " << listaPokemoni[alegere].getNume() << "!\n";
    } else {
        std::cout << "Introdu numarul Pokemonului ales: ";
        std::cin >> alegere;
        alegere--;
    }
    pokemon = listaPokemoni[alegere];
}

Pokemon& Player::getPokemon() { return pokemon; }
const Pokemon& Player::getPokemon() const { return pokemon; }
const std::string& Player::getNume() const { return nume; }

std::ostream& operator<<(std::ostream& out, const Player& p) {
    out << "Jucator: " << p.getNume();
    out << "\nPokemon: " << p.getPokemon().getNume()
        << " (" << p.getPokemon().getTip() << ")";
    return out;
}