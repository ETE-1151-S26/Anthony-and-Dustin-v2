#include <iostream>
#include "Player.hpp"

static const int Start_Bankroll[4] = {0, 1200, 900, 1000 };
static const int Start_Luck[4] = {0, 1, 3, 6 };
static const int Start_HouseEdge[4] = {0, 5, 3, 6 };

Player::Player()
{
    name = "";
    type = HighRoller;
    bankroll = 0;
    luck = 0;
    houseEdge = 0;
}

void Player::initialize(const std::string& playerName, PlayerType playerType)
{
    name = playerName;
    type = playerType;

    bankroll = Start_Bankroll[(int)playerType];
    luck = Start_Luck[(int)playerType];
    houseEdge = Start_HouseEdge[(int)playerType];
}

void Player::showProfile() const
{
    std::cout << "\n=== Profile ===\n";
    std::cout << "Name: " << name << "\n";

    std::cout << "Type: ";
    if (type == HighRoller) std::cout << "High Roller\n";
    else if (type == CardShark) std::cout << "Card Shark\n";
    else std::cout << "Lucky Newbie\n";

    std::cout << "Bankroll: $" << bankroll << "\n";
    std::cout << "Luck: " << luck << "\n";
    std::cout << "House Edge: " << houseEdge << "%\n";
}

void Player::addBankroll(int amount)
{
    bankroll += amount;
    if (houseEdge < 0) houseEdge = 0;
}

int Player::getBankroll() const { return bankroll; }
int Player::getLuck() const { return luck; }
int Player::getHouseEdge() const { return houseEdge; }

Inventory& Player::getInventory() { return inventory; }
const Inventory& Player::getInventory() const { return inventory; }