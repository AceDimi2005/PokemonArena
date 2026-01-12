#include "../headers/FireAbility.h"
#include "../headers/Pokemon.h"
#include "../headers/GameConfig.h"
#include <iostream>
#include <string>


static std::string formatMessage(std::string msg, const std::string& key, const std::string& value) {
    size_t pos;
    while ((pos = msg.find(key)) != std::string::npos) {
        msg.replace(pos, key.length(), value);
    }
    return msg;
}

FireAbility::FireAbility(int power)
    : Ability(), power(power) {}

Ability* FireAbility::clone() const {
    return new FireAbility(*this);
}

void FireAbility::printImpl() const {
    std::cout << "Fire ability, power = " << power << "\n";
}

float FireAbility::getEfficiency(const std::string& adversarTip) const {
    return GameConfig::getInstance().getTypeEfficiency("Foc", adversarTip);
}

void FireAbility::execute(Pokemon& atacator, Pokemon& aparator) const {
    float factor = getEfficiency(aparator.getTip());

    int baseDamage = atacator.getAttack() + power - aparator.getDefense();
    int damage = static_cast<int>(baseDamage * factor);

    if (damage < 0) damage = 0;

    aparator.primesteDamage(damage);

    int buffAmount = 10;
    atacator.modifyAttack(buffAmount);

    std::string msg = GameConfig::getInstance().getMessage("fire_buff");
    msg = formatMessage(msg, "{name}", atacator.getNume());
    msg = formatMessage(msg, "{amount}", std::to_string(buffAmount));

    std::cout << msg;
}