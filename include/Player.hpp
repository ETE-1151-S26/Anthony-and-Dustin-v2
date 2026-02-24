#pragma once
#include <string>
#include "Inventory.hpp"

enum PlayerType//player chooses a type at start that sets starting stats
{
    HighRoller = 1,
    CardShark = 2,
    LuckyNewbie = 3
};

class Player//stores player info, stats, and inventory
{
private:
    std::string name;

    PlayerType type;

    int bankroll;//player money
    int luck;//player luck stat
    int houseEdge;//house edge stat (lower is better for player)

    Inventory inventory;

public:
    Player();

    void initialize(const std::string& playerName, PlayerType playerType);//sets player name, type, and then loads starting stats 

    void showProfile() const;//prints player name, type, and stats
    //stat modification functions
    void addBankroll(int amount);
    void addLuck(int amount);
    void addHouseEdge(int amount);
    //read-only access
    int getBankroll() const;
    int getLuck() const;
    int getHouseEdge() const;
    //inventory access
    Inventory& getInventory();
    const Inventory& getInventory() const;
};