#pragma once

//Item.hpp
//Item represents a purchasable item in the shop that can be applied to affect player stats. 
//Each item has a name, description, traitType (which stat it affects), and traitValue (how much it affects the stat).
//Items are stored in the player's inventory after purchase, and can be applied to modify player stats based on their trait type and value.

#include <string>

//TraitType identifies which player stat an item affects when applied
enum TraitType
{
    Trait_Bankroll,//item changes player's bankroll
    Trait_Luck,//item changes player's luck
    Trait_HouseEdge//item changes casino advantage
};

//Item: stores info about an item that can be bought in the shop and applied to affect player stats
class Item
{
private:
    std::string name;
    std::string description;
    TraitType traitType;//which stat this item affects
    int traitValue;//how much it affects the stat

public:
    Item();
    Item(const std::string& name, const std::string& description, TraitType traitType, int traitValue);

    std::string getName() const;
    std::string getDescription() const;
    TraitType getTraitType() const;
    int getTraitValue() const;
};    