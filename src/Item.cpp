//Item.cpp
//Implements item class constructors and getter functions

#include "Item.hpp"

//default constructor
Item::Item()  
{    
name = "";//item name
description = "";//item description
traitType = Trait_Bankroll;//default trait type
traitValue = 0;//no effect on player stats
}

//parameterized constructor
Item::Item(const std::string& name, const std::string& description, TraitType traitType, int traitValue)
{
    this->name = name;
    this->description = description;
    this->traitType = traitType;
    this->traitValue = traitValue;
}

std::string Item::getName() const
{
    return name;//returns item name
}

std::string Item::getDescription() const
{
    return description;//returns item description
}

TraitType Item::getTraitType() const
{
    return traitType;//returns which player stat the item affects
}

int Item::getTraitValue() const
{
    return traitValue;//returns numerical value of item's effect
}