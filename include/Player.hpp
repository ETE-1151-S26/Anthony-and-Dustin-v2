#pragma once

//Player.hpp 
//defines player class which stores player identity, game statistics, and player's inventory

#include <string>
#include "Inventory.hpp"

enum PlayerType//player chooses a type at start that sets starting bankroll and stats
{
    HighRoller = 1,
    CardShark = 2,
    LuckyNewbie = 3
};

class Player//stores player info, stats, and inventory
{
private:
    std::string name;//player's name

    PlayerType type;//player's starting archetype

    //Core player statistics
    int bankroll;//player's available money
    int luck;//player's luck stat
    int houseEdge;//house advantage stat (lower is better for player)

    //Player's inventory, stores player's currently owned items
    Inventory inventory;

public:
    Player();
    
    void initialize(const std::string& playerName, PlayerType playerType);//initializes player data after name and archetype selection then, sets player name, type, and loads starting stats

    void showProfile() const;//prints player name, type, bankroll, and stats
    
    //stat modification functions
    void addBankroll(int amount);
    void addLuck(int amount);
    void addHouseEdge(int amount);
    
    //read-only access functions
    int getBankroll() const;
    int getLuck() const;
    int getHouseEdge() const;
    
    //inventory access functions, allows classes to modify inventory contents
    Inventory& getInventory();
    const Inventory& getInventory() const;
};