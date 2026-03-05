//Player.cpp
//Implements player functionality including inititalization, stat management, and profile display

#include <iostream>
#include "Player.hpp"

//starting stats tables
//Index 0 is unused so enum values map directly to the correct index in the arrays
static const int Start_Bankroll[4] = {0, 300, 200, 100 };
static const int Start_Luck[4] = {0, 1, 3, 6 };
static const int Start_HouseEdge[4] = {0, 5, 3, 6 };

//Default constructor
Player::Player()
{
    name = "";
    type = HighRoller;
    bankroll = 0;
    luck = 0;
    houseEdge = 0;
}

//Initializes the player with a name and selected archetype
void Player::initialize(const std::string& playerName, PlayerType playerType)
{
    name = playerName;
    type = playerType;
    
    //load starting stats based on type
    bankroll = Start_Bankroll[(int)playerType];
    luck = Start_Luck[(int)playerType];
    houseEdge = Start_HouseEdge[(int)playerType];
}

//Displays player info and current stats
void Player::showProfile() const
{
    std::cout << "\n=== Profile ===\n";
    std::cout << "Name: " << name << "\n";

    std::cout << "Type: ";

    if (type == HighRoller) 
        std::cout << "High Roller\n";
    else if (type == CardShark) 
        std::cout << "Card Shark\n";
    else 
        std::cout << "Lucky Newbie\n";

    //Display player statistics    
    std::cout << "Bankroll: $" << bankroll << "\n";
    std::cout << "Luck: " << luck << "\n";
    std::cout << "House Edge: " << houseEdge << "%\n";
}

//Adds or subtracts money from the player's bankroll
//Used after games, purchases, or applying items
void Player::addBankroll(int amount)
{
    bankroll += amount;
    if (bankroll < 0) 
        bankroll = 0;//bankroll can't be negative
}

//Modifies player's luck stat
void Player::addLuck(int amount)
{
    luck += amount;
    if (luck < 0) luck = 0;//luck can't be negative
}

//Modifies player's house edge stat
void Player::addHouseEdge(int amount)
{
    houseEdge += amount;
    if (houseEdge < 0) 
        houseEdge = 0;//house edge can't be negative
}

//Getter functions
int Player::getBankroll() const 
{ 
    return bankroll; 
}

int Player::getLuck() const 
{ 
    return luck; 
}

int Player::getHouseEdge() const 
{ 
    return houseEdge; 
}

Inventory& Player::getInventory()
{ 
    return inventory; 
}

const Inventory& Player::getInventory() const 
{ 
    return inventory; 
}