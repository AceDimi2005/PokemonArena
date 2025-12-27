//
// Created by Dimitrie Pirvanescu on 20.12.2025.
//

//#ifndef OOP_ABILITY_H
//#define OOP_ABILITY_H

//#endif //OOP_ABILITY_H

#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>

class Ability {
public:
    // destructor virtual OBLIGATORIU
    virtual ~Ability() = default;

    // funcție virtuală PURĂ – specifică temei
    virtual int use(int atk, int def,
                const std::string& adversarTip) const = 0;

    // constructor virtual (clone)
    virtual Ability* clone() const = 0;

    // interfață NON-virtuală
    void print() const {
        printImpl();
    }

protected:
    // afișare virtuală
    virtual void printImpl() const = 0;
};

#endif