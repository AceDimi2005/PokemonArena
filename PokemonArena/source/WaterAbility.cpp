#include "../headers/WaterAbility.h"
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

WaterAbility::WaterAbility(int m)
    : multiplier(m) {}

Ability* WaterAbility::clone() const {
    return new WaterAbility(*this);
}

void WaterAbility::printImpl() const {
    std::cout << "Water ability, multiplier = " << multiplier << "\n";
}

float WaterAbility::getEfficiency(const std::string& adversarTip) const {
    return GameConfig::getInstance().getTypeEfficiency("Apa", adversarTip);
}

void WaterAbility::execute(Pokemon& atacator, Pokemon& aparator) const {
    float factor = getEfficiency(aparator.getTip());

    int damage = (atacator.getAttack() * multiplier) - aparator.getDefense();
    if (damage < 0) damage = 0;
    damage = static_cast<int>(damage * factor);

    aparator.primesteDamage(damage);

    int healAmount = damage / 2;
    atacator.heal(healAmount);

    std::string msg = GameConfig::getInstance().getMessage("water_steal");
    msg = formatMessage(msg, "{name}", atacator.getNume());
    msg = formatMessage(msg, "{amount}", std::to_string(healAmount));

    std::cout << msg;
}