#include "../headers/WaterAbility.h"
#include <iostream>

static float eficientaTip(const std::string& atacant, const std::string& adversar) {
    if (atacant == "Apa" && adversar == "Foc") return 2.0f;
    if (atacant == "Apa" && adversar == "Iarba") return 0.5f;
    return 1.0f;
}

WaterAbility::WaterAbility(int m)
    : multiplier(m) {}

int WaterAbility::use(int atk, int def, const std::string& adversarTip) const {
    float factor = eficientaTip("Apa", adversarTip);
    return static_cast<int>((atk * multiplier - def) * factor);
}

Ability* WaterAbility::clone() const {
    return new WaterAbility(*this);
}

void WaterAbility::printImpl() const {
    std::cout << "Water ability, multiplier = " << multiplier << "\n";
}