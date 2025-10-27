#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Pokemon.h"

class Player {
private:
    std::string nume;
    Pokemon* pokemon;

public:
    explicit Player(std::string nume = "Player");
    ~Player();

    void alegePokemon(std::vector<Pokemon*>& listaPokemoni, bool eAI = false);
    Pokemon* getPokemon() const;
    std::string getNume() const;

};

#endif
