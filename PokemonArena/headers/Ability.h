#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
class Pokemon;
class Ability {
public:
    virtual ~Ability() = default;

    virtual float getEfficiency(const std::string& adversarTip) const = 0;

    /*virtual int use(int atk, int def,
                const std::string& adversarTip) const = 0;
*/
    virtual void execute(Pokemon& atacator, Pokemon& aparator) const = 0;

    virtual Ability* clone() const = 0;

    virtual int getCooldown() const = 0;

    void print() const {
        printImpl();
    }

protected:
    virtual void printImpl() const = 0;
};

#endif