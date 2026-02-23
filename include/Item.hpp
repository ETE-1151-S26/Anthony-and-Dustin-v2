# pragma once
#include <string>

enum TraitType
{
    Trait_Bankroll,
    Trait_Luck,
    Trait_HouseEdge
};

class Item
{
private:
    std::string name;
    std::string description;
    TraitType traitType;
    int traitValue;

public:
    Item();
    Item(const std::string& name, const std::string& description, TraitType traitType, int traitValue);

    std::string getName() const;
    std::string getDescription() const;
    TraitType getTraitType() const;
    int getTraitValue() const;
};    