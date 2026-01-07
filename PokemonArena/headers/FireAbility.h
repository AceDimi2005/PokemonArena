#ifndef FIRE_ABILITY_H
#define FIRE_ABILITY_H

#include "Ability.h"

class FireAbility : public Ability {
    int power;

public:
    explicit FireAbility(int power);

    void execute(Pokemon& atacator, Pokemon& aparator) const override;
    float getEfficiency(const std::string& adversarTip) const override;

    Ability* clone() const override;
    int getCooldown() const override { return 3; }
protected:
    void printImpl() const override;
};

#endif