#include "Ability.h"
class WaterAbility : public Ability {
    int multiplier;
public:
    explicit WaterAbility(int m);
   /* int use(int atk, int def,
        const std::string& adversarTip) const override;*/
    void execute(Pokemon& atacator, Pokemon& aparator) const override;
    float getEfficiency(const std::string& adversarTip) const override;
    Ability* clone() const override;
    int getCooldown() const override { return 2; }
protected:
    void printImpl() const override;
};