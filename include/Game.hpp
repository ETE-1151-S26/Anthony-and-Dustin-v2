#pragma once
#include <string>
#include "Player.hpp"
#include "Item.hpp"

class Game//handles player setup, item management, game state variables, and command helpers
{
private: 
    Player player;
    
    int roundNumber;
    int winStreak;

    static const int Item_List_Size = 10;
    Item itemList[Item_List_Size];//fixed array of items used as item catalog

public:
    Game();
    
    void setup();//setup runs once at start 

    void showHelp() const;//command outputs
    //command handlers (called by main.cpp)
    void cmdProfile() const;
    void cmdInventory() const;
    void cmdInspect(const std::string& itemName) const;
    void cmdApply(const std::string& itemName);

    void cmdPlay();//advances game state
};