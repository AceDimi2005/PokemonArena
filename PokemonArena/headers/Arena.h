#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <iostream>
#include "Player.h"

class Arena {
private:
    std::vector<Pokemon> listaPokemoni;
    static void desfasoaraLupta(Player& p1, Player& p2);

public:
    Arena();
    ~Arena() = default;

    void startGame() const;
    static void salveazaProgres(const Player& p1, const Player& p2);
    static void actualizeazaLeaderboard(const std::string& castigator);
    static void afiseazaLeaderboard();
    friend std::ostream& operator<<(std::ostream& os, const Arena& a);
};

#endif
