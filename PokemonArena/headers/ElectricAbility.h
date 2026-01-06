
#include "Ability.h"
class ElectricAbility : public Ability {
    int bonus;

public:
    explicit ElectricAbility(int bonus);
    void overcharge();
   /* int use(int atk, int def,
        const std::string& adversarTip) const override;*/
    void execute(Pokemon& atacator, Pokemon& aparator) const override;
    float getEfficiency(const std::string& adversarTip) const override;

    Ability* clone() const override;
    int getCooldown() const override { return 3; }

protected:
    void printImpl() const override;
};