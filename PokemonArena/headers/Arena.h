#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <iostream>
#include "Player.h"
#include "BattleHistory.h"

class Arena {
private:
    std::vector<Pokemon> listaPokemoni;

    mutable BattleHistory<std::string> actionHistory;

    mutable BattleHistory<int> damageHistory;

    void desfasoaraLupta(Player& p1, Player& p2) const;

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