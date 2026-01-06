#pragma once
#include <memory>
#include <string>

class Ability;

class AbilityFactory {
public:
    static std::unique_ptr<Ability> create(const std::string& tip);
};