#include "../headers/GameConfig.h"
#include "../headers/GameException.h"
#include "../headers/AbilityFactory.h"
#include <fstream>
#include <iostream>

GameConfig::GameConfig() {
    std::ifstream f("config.json");
    if (!f.is_open()) {
        throw GameException("Nu s-a putut deschide config.json!");
    }
    try {
        data = nlohmann::json::parse(f);
    } catch (const std::exception& e) {
        throw GameException(std::string("Eroare parsare JSON: ") + e.what());
    }
}

GameConfig& GameConfig::getInstance() {
    static GameConfig instance;
    return instance;
}

std::vector<Pokemon> GameConfig::getPokemons() const {
    std::vector<Pokemon> list;
    if (data.contains("pokemons")) {
        for (const auto& el : data["pokemons"]) {
            list.emplace_back(
                el["nume"].get<std::string>(),
                el["tip"].get<std::string>(),
                el["hp"].get<int>(),
                el["attack"].get<int>(),
                el["defense"].get<int>(),
                el["speed"].get<int>()
            );
        }
    }
    return list;
}

float GameConfig::getTypeEfficiency(const std::string& attackerType, const std::string& defenderType) const {
    if (!data.contains("type_chart")) return 1.0f;

    for (const auto& rule : data["type_chart"]) {
        if (rule["attacker"] == attackerType && rule["defender"] == defenderType) {
            return rule["multiplier"].get<float>();
        }
    }
    return 1.0f;
}

std::string GameConfig::getMessage(const std::string& key) const {
    if (data.contains("messages") && data["messages"].contains(key)) {
        return data["messages"][key].get<std::string>();
    }
    return "MISSING MSG: " + key;
}