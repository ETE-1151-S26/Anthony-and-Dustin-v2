#pragma once

//Game.hpp
//Defines the Game class which manages main gameplay loop, commands, shop system, and active casino game

#include <string>
#include "Player.hpp"
#include "Item.hpp"

enum GameType//identifies which casino game is currently active; used by cmdPlay to determine which game function to call
{
    Game_Blackjack = 1,
    Game_Roulette = 2,
    Game_Poker = 3
};

class Game//handles player setup, item management, game state variables, and command helpers
{
private: 
    Player player;//Stores player info, stats, and inventory
    
    int roundNumber;//tracks total rounds played 
    int winStreak;//tracks consecutive wins 

    GameType currentGame;//identifies which casino game is currently active

    static const int Item_Count = 10;//total number of items available in the shop
    Item itemList[Item_Count];//fixed size array of all items available in the shop
    int itemPrice[Item_Count];//parallel array to itemList that stores the price of each item in the shop, itemPrice[i] is the price of itemList[i]
    
public://functions called from main.cpp to respond to player commands
    Game();
    
    void setup();//setup runs once at start 
    void showHelp() const;//command outputs

    //command handlers (called by main.cpp)
    void cmdProfile() const;
    void cmdInventory() const;
    void cmdInspect(const std::string& itemName) const;
    void cmdApply(const std::string& itemName);

    void cmdShop() const;
    void cmdBuy(const std::string& itemName);//handles buying items from the shop, checks if player has enough money and inventory space, then adds item to inventory and deducts cost from bankroll

    void cmdGames() const;
    void cmdSwitch(const std::string& gameName);//changes the player's current game
    
    void cmdPlay();//executes 1 round of the currently active game, updates bankroll, win streak, and round number
};