
#include "Ability.h"
class ElectricAbility : public Ability {
    int bonus;

public:
    explicit ElectricAbility(int bonus);
    void overcharge();
    int use(int atk, int def,
        const std::string& adversarTip) const override;
    Ability* clone() const override;

protected:
    void printImpl() const override;
};