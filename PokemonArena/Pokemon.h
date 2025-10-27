#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>

class Pokemon {
private:
    std::string nume;
    std::string tip;
    int hp;
    int attack;
    int defense;
    int speed;

public:
    Pokemon(std::string nume, std::string tip, int hp, int attack, int defense, int speed);
    ~Pokemon() {}
    std::string getNume() const;
    std::string getTip() const;
    int getHP() const;
    int getAttack() const;
    int getDefense() const;
    int getSpeed() const;
    bool esteViu() const;

    int ataca(Pokemon* adversar);
    void primesteDamage(int damage);

    void setDefending(bool value);
    bool isDefending() const;

    void afiseazaInfo() const;
    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p);
private:
    bool defending = false;
};

#endif
