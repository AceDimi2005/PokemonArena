#include "Pokemon.h"
#include <iostream>

Pokemon::Pokemon(std::string nume, std::string tip, int hp, int attack, int defense, int speed)
    : nume(nume), tip(tip), hp(hp), attack(attack), defense(defense), speed(speed) {}

std::string Pokemon::getNume() const { return nume; }
std::string Pokemon::getTip() const { return tip; }
int Pokemon::getHP() const { return hp; }
int Pokemon::getAttack() const { return attack; }
int Pokemon::getDefense() const { return defense; }
int Pokemon::getSpeed() const { return speed; }
bool Pokemon::esteViu() const { return hp > 0; }

void Pokemon::setDefending(bool value) { defending = value; }
bool Pokemon::isDefending() const { return defending; }

int Pokemon::ataca(Pokemon* adversar) {
    int damage = attack - adversar->defense / 2;
    if (damage < 0) damage = 0;
    adversar->primesteDamage(damage);
    std::cout << nume << " a atacat " << adversar->getNume() << " si a provocat " << damage << " damage!\n";
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

void Pokemon::afiseazaInfo() const {
    std::cout << nume << " (" << tip << ") | HP: " << hp
         << " | Atk: " << attack << " | Def: " << defense
         << " | Spd: " << speed << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
    os << p.nume << " (" << p.tip << ") | HP: " << p.hp
       << " | Atk: " << p.attack << " | Def: " << p.defense
       << " | Spd: " << p.speed;
    return os;
}
