#include "../headers/WaterAbility.h"
#include "../headers/Pokemon.h"
#include <iostream>


WaterAbility::WaterAbility(int m)
    : multiplier(m) {}


Ability* WaterAbility::clone() const {
    return new WaterAbility(*this);
}
void WaterAbility::printImpl() const {
    std::cout << "Water ability, multiplier = " << multiplier << "\n";
}

float WaterAbility::getEfficiency(const std::string& adversarTip) const {
    if (adversarTip == "Foc") return 2.0f;
    if (adversarTip == "Iarba") return 0.5f;
    if (adversarTip == "Electric") return 1.0f;
    return 1.0f;
}

void WaterAbility::execute(Pokemon& atacator, Pokemon& aparator) const {
    float factor = getEfficiency(aparator.getTip());
    int damage = (atacator.getAttack() * multiplier) - aparator.getDefense();
    if (damage < 0) damage = 0;
    damage = static_cast<int>(damage * factor);

    aparator.primesteDamage(damage);

    int healAmount = damage / 2;
    atacator.heal(healAmount);

    std::cout << atacator.getNume() << " a furat " << healAmount << " HP de la inamic!\n";
}