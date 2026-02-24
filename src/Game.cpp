#include <iostream>
#include <cstdlib>
#include "Game.hpp"

Game::Game()
{
    roundNumber = 0;
    winStreak = 0;

    itemList[0] = Item("chips50", "A stack of chips worth fifty dollars.", Trait_Bankroll, 50);
    itemList[1] = Item("chips100", "A stack of chips worth one hundred dollars.", Trait_Bankroll, 100);
    itemList[2] = Item("chips200", "A stack of chips worth two hundred dollars.", Trait_Bankroll, 200);
    itemList[3] = Item("vaultcoupon", "A coupon redeemable for cash at the cage.", Trait_Bankroll, 300);
    itemList[4] = Item("luckyshirt", "A shirt that makes you feel unbeatable.", Trait_Luck, 1);
    itemList[5] = Item("rabbitfoot", "A rabbit's foot that brings good luck to the holder.", Trait_Luck, 1);
    itemList[6] = Item("goldbracelet", "A gold bracelet that seems to shimmer with an otherworldly light.", Trait_Luck, 2);
    itemList[7] = Item("cardguide", "A guidebook that provides insights into the cards and their probabilities.", Trait_HouseEdge, -1);
    itemList[8] = Item("vipband", "A VIP wristband that gets you friendlier rules from the dealer.", Trait_HouseEdge, -1);
    itemList[9] = Item("pitbossfavor", "A favor from the pit boss that lowers the pressure at the table.", Trait_HouseEdge, -2);
}

void Game::setup()
{
    std::string name;
    int choice;

    std::cout <<"Enter your name: ";
    std::cin >>name;

    std::cout <<"\nChoose your player type:\n";
    std::cout << "1) High Roller (Bankroll 1200, Luck 1)\n";
    std::cout << "2) Card Shark (Bankroll 900, Luck 3)\n";
    std::cout << "3) Lucky Newbie (Bankroll 1000, Luck 6)\n";
    std::cout << "Enter choice (1-3): ";
    std::cin >> choice;

if (choice < 1 || choice > 3) choice = 3;

player.initialize(name, (PlayerType)choice);

//starter Inventory
player.getInventory().addItem(itemList[0]);//chips50
player.getInventory().addItem(itemList[4]);//luckyshirt
player.getInventory().addItem(itemList[7]);//cardguide

std::cout << "\nType 'help' to see available commands.\n";
}

void Game::showHelp() const
{
    std::cout << "\n=== Commands ===\n";
    std::cout << "help\n";
    std::cout << "profile\n";
    std::cout << "inventory\n";
    std::cout << "inspect <item>\n";
    std::cout << "apply <item>\n";
    std::cout << "play\n";
    std::cout << "quit\n";
}

void Game::cmdProfile() const
{
    player.showProfile();
    std::cout << "Round Number: " << roundNumber << "\n";
    std::cout << "Win Streak: " << winStreak << "\n";
}

void Game::cmdInventory() const
{
    player.getInventory().display();
}

void Game::cmdInspect(const std::string& itemName) const
{
    Item item;
    if (!player.getInventory().getItemByName(itemName, item))
    {
        std::cout << "You don't have '" << itemName << "'.\n";
        return;
    }

    std::cout << "\n=== Inspect: " << item.getName() << " ===\n";
    std::cout << item.getDescription() << "\n";
    std::cout << "Trait Value: " << item.getTraitValue() << "\n";
}

void Game::cmdApply(const std::string& itemName)
{
    Item item;
    if (!player.getInventory().getItemByName(itemName, item))
    {
        std::cout << "You don't have '" << itemName << "'.\n";
        return;
    }

    if (item.getTraitType() == Trait_Bankroll) player.addBankroll(item.getTraitValue());
    else if (item.getTraitType() == Trait_Luck) player.addLuck(item.getTraitValue());
    else if (item.getTraitType() == Trait_HouseEdge) player.addHouseEdge(item.getTraitValue());

    //Use item when applied
    player.getInventory().removeItemByName(itemName);

    std::cout << "You applied '" << itemName << "'.\n";
}

void Game::cmdPlay()
{
    //advances game state
    roundNumber++;

    //simple quick bet using stats (placeholder until blackjack is integrated)
    int roll = std::rand() % 100;
    int threshold = 50 + player.getLuck();
    threshold -= player.getHouseEdge();

    if (roll < threshold)
    {
        winStreak++;
        player.addBankroll(50);
        std::cout << "You won a quick bet! +$50\n";
    }

    else
    {
        winStreak = 0;
        player.addBankroll(-50);
        std::cout << "You lost a quick bet. -$50\n";
    }
}    