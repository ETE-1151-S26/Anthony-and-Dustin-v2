# pragma once
#include <string>

enum TraitType
{
    Trait_Bankroll,//applying item changes player's bankroll
    Trait_Luck,//applying item changes player's luck
    Trait_HouseEdge//applying item changes house edge
};

class Item
{
private:
    std::string name;
    std::string description;
    TraitType traitType;//affected stat
    int traitValue;//how much it affects the stat

public:
    Item();
    Item(const std::string& name, const std::string& description, TraitType traitType, int traitValue);

    std::string getName() const;
    std::string getDescription() const;
    TraitType getTraitType() const;
    int getTraitValue() const;
};    