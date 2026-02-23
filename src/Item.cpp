#include "Item.hpp"
Item::Item() : name(""), description(""), traitType(Trait_Bankroll), traitValue(0) 
{
}

Item::Item(const std::string& name, const std::string& description, TraitType traitType, int traitValue)
    
: name(name), description(description), traitType(traitType), traitValue(traitValue) 
{
}

std::string Item::getName() const 
{
    return name;
}

std::string Item::getDescription() const 
{
    return description;
}

TraitType Item::getTraitType() const 
{
    return traitType;
}

int Item::getTraitValue() const 
{
    return traitValue;
}