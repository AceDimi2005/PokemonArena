//
// Created by Dimitrie Pirvanescu on 20.12.2025.
//

//#ifndef OOP_WATERABILITY_H
//#define OOP_WATERABILITY_H

//#endif //OOP_WATERABILITY_H
#include "Ability.h"
class WaterAbility : public Ability {
    int multiplier;
public:
    explicit WaterAbility(int m);
    int use(int atk, int def,
        const std::string& adversarTip) const override;
    Ability* clone() const override;
protected:
    void printImpl() const override;
};