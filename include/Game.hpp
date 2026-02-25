#pragma once
#include <string>
#include "Player.hpp"
#include "Item.hpp"

enum GameType
{
    Game_Blackjack = 1,
    Game_Roulette = 2,
    Game_Poker = 3
};

class Game//handles player setup, item management, game state variables, and command helpers
{
private: 
    Player player;
    
    int roundNumber;
    int winStreak;

    GameType currentGame;

    static const int Item_Count = 10;
    Item itemList[Item_Count];
    int itemPrice[Item_Count];
    
public:
    Game();
    
    void setup();//setup runs once at start 
    void showHelp() const;//command outputs

    //command handlers (called by main.cpp)
    void cmdProfile() const;
    void cmdInventory() const;
    void cmdInspect(const std::string& itemName) const;
    void cmdApply(const std::string& itemName);

    void cmdShop() const;
    void cmdBuy(const std::string& itemName);

    void cmdGames() const;
    void cmdSwitch(const std::string& gameName);
    
    void cmdPlay();//advances game state
};