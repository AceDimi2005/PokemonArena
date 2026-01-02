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