#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>
#include <memory>

class Ability;

template <typename T>
T applyModifier(T baseValue, T modifier, T minValue = 0) {
    T result = baseValue + modifier;
    return (result < minValue) ? minValue : result;
}

class Pokemon {
private:
    int cooldown;
    int cooldownMax;
    bool defending;
    std::string nume;
    std::string tip;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int speed;
    std::unique_ptr<Ability> abilitate;
    bool stunned = false;
    int defenseBoost = 0;

public:
    Pokemon(std::string nume, std::string tip, int hp, int attack, int defense, int speed);
    Pokemon(std::string nume, std::string tip, int hp, int attack, int defense, int speed, const Ability& ability);
    Pokemon();
    Pokemon(const Pokemon& other);
    Pokemon& operator=(Pokemon other);
    ~Pokemon();

    void heal(int amount);
    void modifyDefense(int amount);
    void modifyAttack(int amount) { attack = applyModifier<int>(attack, amount); }

    void setStunned(bool val) { stunned = val; }
    [[nodiscard]] bool isStunned() const { return stunned; }
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getTip() const;
    [[nodiscard]] int getHP() const;
    [[nodiscard]] int getDefense() const;
    [[nodiscard]] int getSpeed() const;
    [[nodiscard]] bool esteViu() const;
    void valideaza() const;
    [[nodiscard]] int getAttack() const;
    void reseteazaAbilitatea();
    [[nodiscard]] bool poateFolosiiAbilitatea() const;
    void reduceCooldown();
    int folosesteAbilitate(Pokemon& adversar);

    static float eficientaTip(const std::string& tipAtacant, const std::string& tipAdversar);

    int ataca(Pokemon& adversar) const;
    void primesteDamage(int damage);

    void setDefending(bool value);

    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p);
    friend void swap(Pokemon& a, Pokemon& b) noexcept;
};

#endif