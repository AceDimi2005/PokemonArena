#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <iostream>
#include "Player.h"

class Arena {
private:
    std::vector<Pokemon*> listaPokemoni;

    void desfasoaraLupta(Player& p1, Player& p2);

public:
    Arena();
    ~Arena();

    void startGame();

    friend std::ostream& operator<<(std::ostream& os, const Arena& a);
};

#endif
