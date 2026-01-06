#include "../headers/AbilityFactory.h"
#include "../headers/FireAbility.h"
#include "../headers/WaterAbility.h"
#include "../headers/ElectricAbility.h"
#include "../headers/GrassAbility.h"
#include "../headers/GameException.h"

std::unique_ptr<Ability> AbilityFactory::create(const std::string& tip) {
    if (tip == "Foc")
        return std::make_unique<FireAbility>(20);

    if (tip == "Apa")
        return std::make_unique<WaterAbility>(2);

    if (tip == "Electric")
        return std::make_unique<ElectricAbility>(15);

    if (tip == "Iarba")
        return std::make_unique<GrassAbility>(18);

    throw AbilityException();
}