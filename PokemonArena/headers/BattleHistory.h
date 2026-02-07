#ifndef BATTLE_HISTORY_H
#define BATTLE_HISTORY_H

#include <vector>
#include <iostream>
#include <numeric>

template <typename T>
class BattleHistory {
private:
    std::vector<T> entries;
public:
    void add(const T& entry) {
        entries.push_back(entry);
    }

    void showAll(const std::string& title) const {
        std::cout << "\n--- " << title << " ---\n";
        for (const auto& e : entries) {
            std::cout << " > " << e << "\n";
        }
    }

    T getTotalValue() const {
        return std::accumulate(entries.begin(), entries.end(), T{});
    }
};

#endif