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

    Player(const Player& other);
    Player& operator=(const Player& other);

    void setPokemon(Pokemon* pokemon);

    void alegePokemon(const std::vector<Pokemon*>& listaPokemoni, bool eAI = false);
    [[nodiscard]] Pokemon* getPokemon() const;
    [[nodiscard]] const std::string& getNume() const;
    friend std::ostream& operator<<(std::ostream& os, const Player& p);

};

#endif
