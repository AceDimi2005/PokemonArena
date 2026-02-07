#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Pokemon.h"

class GameConfig {
private:
    nlohmann::json data;
    GameConfig();

public:
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    static GameConfig& getInstance();

    std::vector<Pokemon> getPokemons() const;
    float getTypeEfficiency(const std::string& attackerType, const std::string& defenderType) const;
    std::string getMessage(const std::string& key) const;
};