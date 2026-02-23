#pragma once
#include <string>
#include "Inventory.hpp"

enum PlayerType
{
    HighRoller = 1,
    CardShark = 2,
    LuckyNewbie = 3
};

class Player
{
private:
    std::string name;

    PlayerType type;

    int bankroll;
    int luck;
    int houseEdge;

    Inventory inventory;

public:
    Player();

    void initialize(const std::string& playerName, PlayerType playerType);

    void showProfile() const;

    void addBankroll(int amount);
    void addLuck(int amount);
    void addHouseEdge(int amount);

    int getBankroll() const;
    int getLuck() const;
    int getHouseEdge() const;

    Inventory& getInventory();
    const Inventory& getInventory() const;
};