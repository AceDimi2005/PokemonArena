//
// Created by Dimitrie Pirvanescu on 20.12.2025.
//

//#ifndef OOP_ELECTRICABILITY_H
//#define OOP_ELECTRICABILITY_H

//#endif //OOP_ELECTRICABILITY_H
#include "Ability.h"
class ElectricAbility : public Ability {
    int bonus;   // 🔥 același nume ca în cpp

public:
    explicit ElectricAbility(int bonus);
    void overcharge();
    int use(int atk, int def,
        const std::string& adversarTip) const override;
    Ability* clone() const override;

protected:
    void printImpl() const override;
};