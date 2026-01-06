#include "../headers/FireAbility.h"
#include "../headers/Pokemon.h"


FireAbility::FireAbility(int power)
    : Ability(), power(power) {}

/*int FireAbility::use(int attackerAtk, int defenderDef, const std::string& adversarTip) const {
    float factor = eficientaTip("Foc", adversarTip);
    int damage = static_cast<int>((attackerAtk + power - defenderDef) * factor);
    return damage > 0 ? damage : 0;
}*/

/*Ability* FireAbility::clone() const {
    return new FireAbility(*this);
}
*/

Ability* FireAbility::clone() const {
    return new FireAbility(*this);
}
void FireAbility::printImpl() const {
    std::cout << "Fire ability, power = " << power << "\n";
}
float FireAbility::getEfficiency(const std::string& adversarTip) const {
    if (adversarTip == "Iarba") return 2.0f;
    if (adversarTip == "Apa") return 0.5f;
    return 1.0f;
}

void FireAbility::execute(Pokemon& atacator, Pokemon& aparator) const {

    float factor = getEfficiency(aparator.getTip());


    int baseDamage = atacator.getAttack() + power - aparator.getDefense();
    int damage = static_cast<int>(baseDamage * factor);

    if (damage < 0) damage = 0;


    aparator.primesteDamage(damage);


    int buffAmount = 10;
    atacator.modifyAttack(buffAmount);

    std::cout << atacator.getNume() << " se infierbanta! Atacul i-a crescut cu "
              << buffAmount << " puncte!\n";
}