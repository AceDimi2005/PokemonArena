#ifndef FIRE_ABILITY_H
#define FIRE_ABILITY_H

#include "Ability.h"

class FireAbility : public Ability {
    int power;

public:
    explicit FireAbility(int power);

    int use(int atk, int def,
        const std::string& adversarTip) const override;
    Ability* clone() const override;

protected:
    void printImpl() const override;
};

#endif