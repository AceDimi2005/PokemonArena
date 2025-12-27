#include "../headers/ElectricAbility.h"
#include <iostream>

static float eficientaTip(const std::string& atacant, const std::string& adversar) {
    if (atacant == "Electric" && adversar == "Apa") return 2.0f;
    if (atacant == "Electric" && adversar == "Iarba") return 0.5f;
    return 1.0f;
}

ElectricAbility::ElectricAbility(int bonus)
    : bonus(bonus) {}

int ElectricAbility::use(int atk, int /*def*/, const std::string& adversarTip) const {
    float factor = eficientaTip("Electric", adversarTip);
    return static_cast<int>((atk + bonus) * factor);
}

Ability* ElectricAbility::clone() const {
    return new ElectricAbility(*this);
}

void ElectricAbility::printImpl() const {
    std::cout << "Electric ability, bonus = " << bonus << "\n";
}

void ElectricAbility::overcharge() {
    bonus += 10;
}