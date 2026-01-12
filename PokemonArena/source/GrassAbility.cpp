#include "../headers/GrassAbility.h"
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

GrassAbility::GrassAbility(int power)
    : power(power) {}

float GrassAbility::getEfficiency(const std::string& adversarTip) const {
    return GameConfig::getInstance().getTypeEfficiency("Iarba", adversarTip);
}

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

        std::string msg = GameConfig::getInstance().getMessage("grass_recoil");
        msg = formatMessage(msg, "{name}", atacator.getNume());
        msg = formatMessage(msg, "{amount}", std::to_string(recoil));
        std::cout << msg;
    }
}