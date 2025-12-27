#include "../headers/GrassAbility.h"
#include <iostream>

static float eficientaTip(const std::string& atacant,
                          const std::string& adversar) {
    if (atacant == "Iarba" && adversar == "Apa") return 2.0f;
    if (atacant == "Iarba" && adversar == "Foc") return 0.5f;
    return 1.0f;
}

GrassAbility::GrassAbility(int power)
    : power(power) {}

int GrassAbility::use(int atk, int def,
                      const std::string& adversarTip) const {
    float factor = eficientaTip("Iarba", adversarTip);
    int damage = static_cast<int>((atk + power - def) * factor);
    return damage > 0 ? damage : 0;
}
Ability* GrassAbility::clone() const {
    return new GrassAbility(*this);
}

void GrassAbility::printImpl() const {
    std::cout << "Grass ability (Vine Whip), power = " << power << "\n";
}