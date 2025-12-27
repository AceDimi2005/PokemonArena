#include "../headers/FireAbility.h"

static float eficientaTip(const std::string& atacant, const std::string& adversar) {
    if (atacant == "Foc" && adversar == "Iarba") return 2.0f;
    if (atacant == "Foc" && adversar == "Apa") return 0.5f;
    return 1.0f;
}

FireAbility::FireAbility(int power)
    : Ability(), power(power) {}

int FireAbility::use(int attackerAtk, int defenderDef, const std::string& adversarTip) const {
    float factor = eficientaTip("Foc", adversarTip);
    int damage = static_cast<int>((attackerAtk + power - defenderDef) * factor);
    return damage > 0 ? damage : 0;
}

Ability* FireAbility::clone() const {
    return new FireAbility(*this);
}

void FireAbility::printImpl() const {
    std::cout << "Fire ability, power = " << power << "\n";
}