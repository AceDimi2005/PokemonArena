#ifndef GRASS_ABILITY_H
#define GRASS_ABILITY_H

#include "Ability.h"
#include <string>

class GrassAbility : public Ability {
    int power;

public:
    explicit GrassAbility(int power);

    void execute(Pokemon& atacator, Pokemon& aparator) const override;
    float getEfficiency(const std::string& adversarTip) const override;

    Ability* clone() const override;
    int getCooldown() const override { return 2; }

protected:
    void printImpl() const override;
};

#endif