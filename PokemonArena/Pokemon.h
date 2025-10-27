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
    bool defending;

public:
    Pokemon(std::string nume, std::string tip, int hp, int attack, int defense, int speed);
    ~Pokemon() = default;
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getTip() const;
    [[nodiscard]] int getHP() const;
    [[nodiscard]] int getAttack() const;
    [[nodiscard]] int getDefense() const;
    [[nodiscard]] int getSpeed() const;
    [[nodiscard]] bool esteViu() const;

    int ataca(Pokemon* adversar) const;
    void primesteDamage(int damage);

    void setDefending(bool value);
    [[nodiscard]] bool isDefending() const;

    void afiseazaInfo() const;
    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p);

};

#endif
