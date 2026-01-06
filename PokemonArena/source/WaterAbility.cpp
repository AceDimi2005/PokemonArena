#include "../headers/WaterAbility.h"
#include "../headers/Pokemon.h"
#include <iostream>


WaterAbility::WaterAbility(int m)
    : multiplier(m) {}

/*int WaterAbility::use(int atk, int def, const std::string& adversarTip) const {
    float factor = eficientaTip("Apa", adversarTip);
    return static_cast<int>((atk * multiplier - def) * factor);
}

Ability* WaterAbility::clone() const {
    return new WaterAbility(*this);
}*/

Ability* WaterAbility::clone() const {
    return new WaterAbility(*this);
}
void WaterAbility::printImpl() const {
    std::cout << "Water ability, multiplier = " << multiplier << "\n";
}

float WaterAbility::getEfficiency(const std::string& adversarTip) const {
    if (adversarTip == "Foc") return 2.0f;   // Apa stinge Focul (Super Eficient)
    if (adversarTip == "Iarba") return 0.5f; // Apa e slabă la Iarbă (Nu e eficient)
    if (adversarTip == "Electric") return 1.0f; // Neutru
    return 1.0f; // Default
}

// WaterAbility.cpp
void WaterAbility::execute(Pokemon& atacator, Pokemon& aparator) const {
    // 1. Calculează damage (poți folosi helper-ul de eficiență discutat anterior)
    float factor = getEfficiency(aparator.getTip());
    int damage = (atacator.getAttack() * multiplier) - aparator.getDefense();
    if (damage < 0) damage = 0;
    damage = static_cast<int>(damage * factor);

    // 2. Aplică damage
    aparator.primesteDamage(damage);

    // 3. LOGICĂ UNICĂ: Vindecă atacatorul cu 50% din damage-ul dat
    int healAmount = damage / 2;
    atacator.heal(healAmount);

    std::cout << atacator.getNume() << " a furat " << healAmount << " HP de la inamic!\n";
}