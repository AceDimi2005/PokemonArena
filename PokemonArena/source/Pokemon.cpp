#include "../headers/Pokemon.h"
#include "../headers/Ability.h"
#include "../headers/AbilityFactory.h"
#include "../headers/GameConfig.h"
#include "../headers/ElectricAbility.h"
#include "../headers/GameException.h"

#include <iostream>
#include <utility>
#include <memory>
#include <string>

static std::string formatMessage(std::string msg, const std::string& key, const std::string& value) {
    size_t pos;
    while ((pos = msg.find(key)) != std::string::npos) {
        msg.replace(pos, key.length(), value);
    }
    return msg;
}

void Pokemon::heal(int amount) {
    hp += amount;
    if (hp > maxHp) {
        hp = maxHp;
    }

    std::string msg = GameConfig::getInstance().getMessage("heal_msg");
    msg = formatMessage(msg, "{name}", nume);
    msg = formatMessage(msg, "{amount}", std::to_string(amount));
    std::cout << msg;
}

void Pokemon::valideaza() const {
    if (hp <= 0 || attack < 0 || defense < 0 || speed < 0)
        throw InvalidPokemonException();

    if (!abilitate)
        throw AbilityException();
}

Pokemon::Pokemon()
    : cooldown(0), cooldownMax(0), defending(false),
      nume(""), tip(""), hp(0), maxHp(0), attack(0), defense(0), speed(0),
      abilitate(nullptr) {}

Pokemon::Pokemon(std::string nume, std::string tip, int hp, int attack, int defense, int speed)
    : cooldown(0), cooldownMax(0), defending(false),
      nume(std::move(nume)), tip(std::move(tip)),
      hp(hp), maxHp(hp), attack(attack), defense(defense), speed(speed),
      abilitate(AbilityFactory::create(this->tip)) {

    if (abilitate) {
        cooldownMax = abilitate->getCooldown();
    } else {
        cooldownMax = 0;
    }

    cooldown = 0;
}

Pokemon::Pokemon(const Pokemon& other)
    : cooldown(other.cooldown), cooldownMax(other.cooldownMax), defending(other.defending),
      nume(other.nume), tip(other.tip), hp(other.hp), maxHp(other.maxHp), attack(other.attack),
      defense(other.defense), speed(other.speed),
      abilitate(other.abilitate ? other.abilitate->clone() : nullptr) {}

Pokemon& Pokemon::operator=(Pokemon other) {
    swap(*this, other);
    return *this;
}

void swap(Pokemon& a, Pokemon& b) noexcept {
    using std::swap;
    swap(a.cooldown, b.cooldown);
    swap(a.cooldownMax, b.cooldownMax);
    swap(a.defending, b.defending);
    swap(a.nume, b.nume);
    swap(a.tip, b.tip);
    swap(a.hp, b.hp);
    swap(a.maxHp, b.maxHp);
    swap(a.attack, b.attack);
    swap(a.defense, b.defense);
    swap(a.speed, b.speed);
    swap(a.abilitate, b.abilitate);
}

Pokemon::~Pokemon() = default;

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

int Pokemon::folosesteAbilitate(Pokemon& adversar) {
    if (!poateFolosiiAbilitatea()) {
        std::string msg = GameConfig::getInstance().getMessage("ability_cooldown");
        msg = formatMessage(msg, "{name}", nume);
        msg = formatMessage(msg, "{cooldown}", std::to_string(cooldown));
        std::cout << msg;
        return 0;
    }

    if (!abilitate)
        throw AbilityException();

    if (auto* electric = dynamic_cast<ElectricAbility*>(abilitate.get())) {
        electric->overcharge();
        std::string msg = GameConfig::getInstance().getMessage("electric_overcharge");
        msg = formatMessage(msg, "{name}", nume);
        std::cout << msg;
    }

    abilitate->print();

    abilitate->execute(*this, adversar);
    reseteazaAbilitatea();
    return 0;
}

const std::string& Pokemon::getNume() const { return nume; }
const std::string& Pokemon::getTip() const { return tip; }
int Pokemon::getHP() const { return hp; }
int Pokemon::getDefense() const { return defense; }
int Pokemon::getSpeed() const { return speed; }
bool Pokemon::esteViu() const { return hp > 0; }

void Pokemon::setDefending(bool value) { defending = value; }
int Pokemon::getAttack() const {
    return attack;
}

float Pokemon::eficientaTip(const std::string& tipAtacant, const std::string& tipAdversar) {
    return GameConfig::getInstance().getTypeEfficiency(tipAtacant, tipAdversar);
}

int Pokemon::ataca(Pokemon& adversar) const {
    const float factor = eficientaTip(tip, adversar.getTip());
    int damage = static_cast<int>((attack - adversar.getDefense() / 2.0) * factor);
    if (damage < 0) damage = 0;

    adversar.primesteDamage(damage);

    std::string msg = GameConfig::getInstance().getMessage("attack_msg");
    msg = formatMessage(msg, "{attacker}", nume);
    msg = formatMessage(msg, "{defender}", adversar.getNume());
    msg = formatMessage(msg, "{damage}", std::to_string(damage));
    std::cout << msg;

    if (factor > 1.0f) {
        std::cout << GameConfig::getInstance().getMessage("super_effective");
    } else if (factor < 1.0f) {
        std::cout << GameConfig::getInstance().getMessage("not_very_effective");
    }

    return damage;
}

void Pokemon::primesteDamage(int damage) {
    if (defending) {
        damage /= 2;
        std::string msg = GameConfig::getInstance().getMessage("defense_msg");
        msg = formatMessage(msg, "{name}", nume);
        msg = formatMessage(msg, "{damage}", std::to_string(damage));
        std::cout << msg;
        defending = false;
    }

    hp -= damage;
    if (hp < 0) hp = 0;
}

std::ostream& operator<<(std::ostream& out, const Pokemon& p) {
    out << "Pokemon: " << p.nume << " (" << p.tip << ")\n"
        << "HP: " << p.hp
        << " | Atk: " << p.attack
        << " | Def: " << p.defense
        << " | Spd: " << p.speed
        << " | Cooldown: " << p.cooldown << "/" << p.cooldownMax;
    return out;
}