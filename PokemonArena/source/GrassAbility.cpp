#include "../headers/GrassAbility.h"
#include "../headers/Pokemon.h"
#include <iostream>


float GrassAbility::getEfficiency(const std::string& adversarTip) const {
    if (adversarTip == "Apa") return 2.0f;
    if (adversarTip == "Foc") return 0.5f;
    return 1.0f;
}

GrassAbility::GrassAbility(int power)
    : power(power) {}


Ability* GrassAbility::clone() const {
    return new GrassAbility(*this);
}
void GrassAbility::printImpl() const {
    std::cout << "Grass ability (Vine Whip), power = " << power << "\n";
}
void GrassAbility::execute(Pokemon& atacator, Pokemon& aparator) const {
    float factor = getEfficiency(aparator.getTip());

    int baseDamage = atacator.getAttack() + static_cast<int>(power * 1.5) - aparator.getDefense();
    int damage = static_cast<int>(baseDamage * factor);

    if (damage < 0) damage = 0;

    aparator.primesteDamage(damage);

    int recoil = damage / 3;
    if (recoil > 0) {
        atacator.primesteDamage(recoil);
        std::cout << atacator.getNume() << " a suferit " << recoil
                  << " damage din cauza reculului loviturii puternice!\n";
    }
}