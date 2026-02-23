#pragma once
#include <string>
#include "Player.hpp"
#include "Item.hpp"

class Game
{
private: 
    Player player;
    
    int roundNumber;
    int winStreak;

    static const int Item_List_Size = 10;
    Item itemList[Item_List_Size];

public:
    Game();
    
    void setup();

    void showHelp() const;

    void cmdProfile() const;
    void cmdInventory() const;
    void cmdInspect(const std::string& itemName) const;
    void cmdApply(const std::string& itemName);

    void cmdPlay();//advances game state
};