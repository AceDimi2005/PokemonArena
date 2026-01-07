#include "../headers/ElectricAbility.h"
#include <cstdlib>
#include "../headers/Pokemon.h"
#include <iostream>

float ElectricAbility::getEfficiency(const std::string& adversarTip) const {
    if (adversarTip == "Apa") return 2.0f;
    if (adversarTip == "Iarba") return 0.5f;
    return 1.0f;
}

ElectricAbility::ElectricAbility(int bonus)
    : bonus(bonus) {}

Ability* ElectricAbility::clone() const {
    return new ElectricAbility(*this);
}

void ElectricAbility::printImpl() const {
    std::cout << "Electric ability, bonus = " << bonus << "\n";
}

void ElectricAbility::overcharge() {
    bonus += 10;
}
void ElectricAbility::execute(Pokemon& atacator, Pokemon& aparator) const {
    float factor = getEfficiency(aparator.getTip());


    int ignoredDefense = aparator.getDefense() / 5;
    int baseDamage = (atacator.getAttack() + bonus) - (aparator.getDefense() - ignoredDefense);

    int damage = static_cast<int>(baseDamage * factor);
    if (damage < 0) damage = 0;

    aparator.primesteDamage(damage);


    int chance = std::rand() % 100;
    if (chance < 25) {
        aparator.setStunned(true);
        std::cout << "ZZZT! " << aparator.getNume() << " a fost PARALIZAT de socul electric!\n";
    }
}
