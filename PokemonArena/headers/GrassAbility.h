#ifndef GRASS_ABILITY_H
#define GRASS_ABILITY_H

#include "Ability.h"
#include <string>

class GrassAbility : public Ability {
    int power;

public:
    explicit GrassAbility(int power);

    int use(int atk, int def,
        const std::string& adversarTip) const override;
    Ability* clone() const override;

protected:
    void printImpl() const override;
};

#endif