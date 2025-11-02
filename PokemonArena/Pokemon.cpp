#include "Pokemon.h"
#include <iostream>
#include <utility>

Pokemon::Pokemon(std::string nume, std::string tip, int hp, int attack, int defense, int speed)
    : nume(std::move(nume)), tip(std::move(tip)), hp(hp), attack(attack), defense(defense), speed(speed), defending(false) {
    if (this->tip == "Foc") cooldownMax = 3;
    else if (this->tip == "Apa") cooldownMax = 2;
    else if (this->tip == "Iarba") cooldownMax = 2;
    else if (this->tip == "Electric") cooldownMax = 3;
    else cooldownMax = 2;
    cooldown = 0;
}

void Pokemon::reseteazaAbilitatea() {
    cooldown = cooldownMax;
}

bool Pokemon::poateFolosiiAbilitatea() const {
    return cooldown == 0;
}

void Pokemon::reduceCooldown() {
    if (cooldown > 0)
        cooldown--;
}

int Pokemon::folosesteAbilitate(Pokemon* adversar) {
    if (!poateFolosiiAbilitatea()) {
        std::cout << nume << " nu isi poate folosi abilitatea inca! (" << cooldown << " runde ramase)\n";
        return 0;
    }

    float factor = eficientaTip(tip, adversar->getTip());
    float power = 1.5f;

    if (tip == "Foc") {
        std::cout << nume << " foloseste Flamethrower!\n";
        power = 2.0f;
    } else if (tip == "Apa") {
        std::cout << nume << " foloseste Water Pulse!\n";
        power = 1.6f;
    } else if (tip == "Iarba") {
        std::cout << nume << " foloseste Vine Whip!\n";
        power = 1.5f;
    } else if (tip == "Electric") {
        std::cout << nume << " foloseste Thunderbolt!\n";
        power = 1.8f;
    }

    int damage = static_cast<int>((attack * power - adversar->getDefense() / 3.0) * factor);
    if (damage < 0) damage = 0;

    adversar->primesteDamage(damage);
    std::cout << nume << " a folosit abilitatea speciala si a provocat "
          << damage << " damage adversarului!\n";
    reseteazaAbilitatea();

    if (factor > 1.0f)
        std::cout << "Este super eficient!\n";
    else if (factor < 1.0f)
        std::cout << "Nu e prea eficient...\n";

    return damage;
}

const std::string& Pokemon::getNume() const { return nume; }
const std::string& Pokemon::getTip() const { return tip; }
int Pokemon::getHP() const { return hp; }
int Pokemon::getDefense() const { return defense; }
int Pokemon::getSpeed() const { return speed; }
bool Pokemon::esteViu() const { return hp > 0; }

void Pokemon::setDefending(bool value) { defending = value; }

    float Pokemon::eficientaTip(const std::string& tipAtacant, const std::string& tipAdversar) {
    if (tipAtacant == "Foc" && tipAdversar == "Iarba") return 2.0f;
    if (tipAtacant == "Foc" && tipAdversar == "Apa") return 0.5f;
    if (tipAtacant == "Apa" && tipAdversar == "Foc") return 2.0f;
    if (tipAtacant == "Apa" && tipAdversar == "Iarba") return 0.5f;
    if (tipAtacant == "Iarba" && tipAdversar == "Apa") return 2.0f;
    if (tipAtacant == "Iarba" && tipAdversar == "Foc") return 0.5f;
    if (tipAtacant == "Electric" && tipAdversar == "Apa") return 2.0f;
    if (tipAtacant == "Electric" && tipAdversar == "Iarba") return 0.5f;
    return 1.0f;
}

int Pokemon::ataca(Pokemon* adversar) const {
    const float factor = eficientaTip(tip, adversar->getTip());
    int damage = static_cast<int>((attack - adversar->getDefense() / 2.0) * factor);
    if (damage < 0) damage = 0;
    adversar->primesteDamage(damage);
    std::cout << nume << " a atacat " << adversar->getNume() << " si a provocat " << damage << " damage!\n";
    if (factor > 1.0f)
        std::cout << "Este foarte eficient!\n";
    else if (factor < 1.0f)
        std::cout << "Nu este prea eficient...\n";
    return damage;
}

void Pokemon::primesteDamage(int damage) {
    if (defending) {
        damage /= 2;
        std::cout << nume << " s-a aparat si a redus damage-ul la " << damage << "!\n";
        defending = false;
    }
    hp -= damage;
    if (hp < 0) hp = 0;
}

std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
    os << p.nume << " (" << p.tip << ") | HP: " << p.hp
       << " | Atk: " << p.attack << " | Def: " << p.defense
       << " | Spd: " << p.speed;
    return os;
}
