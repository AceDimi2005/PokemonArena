#include "../headers/Pokemon.h"
#include "../headers/Ability.h"
#include "../headers/AbilityFactory.h"

#include <iostream>
#include <utility>
#include <memory>

#include "../headers/FireAbility.h"
#include "../headers/WaterAbility.h"
#include "../headers/ElectricAbility.h"
#include "../headers/GrassAbility.h"
#include "../headers/GameException.h"

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

/*void Pokemon::reduceCooldown() {
    if (cooldown > 0)
        cooldown--;
}
*/

int Pokemon::folosesteAbilitate(Pokemon& adversar) {
    if (!poateFolosiiAbilitatea()) {
        std::cout << nume << " nu isi poate folosi abilitatea inca! (" << cooldown << " runde ramase)\n";
        return 0;
    }

    if (!abilitate)
        throw AbilityException();

    if (auto* electric = dynamic_cast<ElectricAbility*>(abilitate.get())) {
        electric->overcharge();
        std::cout << nume << " isi incarca electricitatea!\n";
    }

    abilitate->print();

    int damage = abilitate->use(
    attack,
    adversar.getDefense(),
    adversar.getTip()
);
    if (damage < 0) damage = 0;

    adversar.primesteDamage(damage);
    std::cout << nume << " a folosit abilitatea speciala si a provocat "
              << damage << " damage adversarului!\n";

    reseteazaAbilitatea();

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

int Pokemon::ataca(Pokemon& adversar) const {
    const float factor = eficientaTip(tip, adversar.getTip());
    int damage = static_cast<int>((attack - adversar.getDefense() / 2.0) * factor);
    if (damage < 0) damage = 0;

    adversar.primesteDamage(damage);
    std::cout << nume << " a atacat " << adversar.getNume() << " si a provocat " << damage << " damage!\n";

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

std::ostream& operator<<(std::ostream& out, const Pokemon& p) {
    out << "Pokemon: " << p.nume << " (" << p.tip << ")\n"
        << "HP: " << p.hp
        << " | Atk: " << p.attack
        << " | Def: " << p.defense
        << " | Spd: " << p.speed
        << " | Cooldown: " << p.cooldown << "/" << p.cooldownMax;
    return out;
}
