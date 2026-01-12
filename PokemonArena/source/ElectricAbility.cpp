#include "../headers/ElectricAbility.h"
#include "../headers/Pokemon.h"
#include "../headers/GameConfig.h"
#include <iostream>
#include <cstdlib>
#include <string>

static std::string formatMessage(std::string msg, const std::string& key, const std::string& value) {
    size_t pos;
    while ((pos = msg.find(key)) != std::string::npos) {
        msg.replace(pos, key.length(), value);
    }
    return msg;
}

float ElectricAbility::getEfficiency(const std::string& adversarTip) const {
    return GameConfig::getInstance().getTypeEfficiency("Electric", adversarTip);
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

        std::string msg = GameConfig::getInstance().getMessage("stunned_hit_msg");

        msg = formatMessage(msg, "{name}", aparator.getNume());
        std::cout << msg;
    }
}