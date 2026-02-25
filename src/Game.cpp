#include <iostream>
#include <string>
#include <cstdlib>
#include "Game.hpp"
#include "Blackjack.hpp"

static std::string traitTypeToString(TraitType t)
{
    if (t == Trait_Bankroll) return "Bankroll";
    if (t == Trait_Luck) return "Luck";
    return "House Edge";
}

Game::Game()
{
    //Initialize game state variables
    roundNumber = 0;
    winStreak = 0;

    currentGame =Game_Blackjack;//default to blackjack, other games can be added later

    //Bankroll items
    itemList[0] = Item("chips50", "A stack of chips worth fifty dollars.", Trait_Bankroll, 50);
    itemList[1] = Item("chips100", "A stack of chips worth one hundred dollars.", Trait_Bankroll, 100);
    itemList[2] = Item("chips200", "A stack of chips worth two hundred dollars.", Trait_Bankroll, 200);
    itemList[3] = Item("vaultcoupon", "A coupon redeemable for cash at the cage.", Trait_Bankroll, 300);
    
    //Luck items
    itemList[4] = Item("luckyshirt", "A shirt that makes you feel unbeatable.", Trait_Luck, 1);
    itemList[5] = Item("rabbitfoot", "A rabbit's foot that brings good luck to the holder.", Trait_Luck, 1);
    itemList[6] = Item("goldbracelet", "A gold bracelet that seems to shimmer with an otherworldly light.", Trait_Luck, 2);
    
    //House Edge Reducers
    itemList[7] = Item("cardguide", "A guidebook that provides insights into the cards and their probabilities.", Trait_HouseEdge, -1);
    itemList[8] = Item("vipband", "A VIP wristband that gets you friendlier rules from the dealer.", Trait_HouseEdge, -1);
    itemList[9] = Item("pitbossfavor", "A favor from the pit boss that lowers the pressure at the table.", Trait_HouseEdge, -2);

    //Shop Item Prices
    itemPrice[0] = 50;//chips50
    itemPrice[1] = 100;//chips100
    itemPrice[2] = 200;//chips200
    itemPrice[3] = 300;//vaultcoupon
    itemPrice[4] = 75;//luckyshirt
    itemPrice[5] = 60;//rabbitfoot
    itemPrice[6] = 120;//goldbracelet
    itemPrice[7] = 80;//cardguide
    itemPrice[8] = 90;//vipband
    itemPrice[9] = 150;//pitbossfavor
}

void Game::setup()//setup runs once at start, asks for player name, type, then loads starting stats and inventory
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

if (choice < 1 || choice > 3) choice = 3;//Validation(fallback to Lucky Newbie)

player.initialize(name, (PlayerType)choice);

//starter Inventory
player.getInventory().addItem(itemList[0]);//chips50
player.getInventory().addItem(itemList[4]);//luckyshirt
player.getInventory().addItem(itemList[7]);//cardguide

std::cout << "\nType 'help' to see available commands.\n";
}

void Game::showHelp() const//outputs for help command
{
    std::cout << "\n=== Commands ===\n";
    std::cout << "help\n";
    std::cout << "profile\n";
    std::cout << "inventory\n";
    std::cout << "inspect <item>\n";
    std::cout << "apply <item>\n";
    std::cout << "shop\n";
    std::cout << "buy <item>\n";
    std::cout << "games\n";
    std::cout << "switch <game>\n";
    std::cout << "play\n";
    std::cout << "quit\n";
}

void Game::cmdProfile() const//outputs player profile and game state info
{
    player.showProfile();
    std::cout << "Round Number: " << roundNumber << "\n";
    std::cout << "Win Streak: " << winStreak << "\n";
}

void Game::cmdInventory() const//displays inventory 
{
    player.getInventory().display();
}

void Game::cmdInspect(const std::string& itemName) const//looks up item by name in player inventory and displays description and trait value if found
{
    Item item;
    if (!player.getInventory().getItemByName(itemName, item))
    {
        std::cout << "You don't have '" << itemName << "'.\n";
        return;
    }

    std::cout << "\n=== Inspect: " << item.getName() << " ===\n";
    std::cout << item.getDescription() << "\n";
    std::cout << "Trait: " << traitTypeToString(item.getTraitType()) << " (";
    int v = item.getTraitValue();
    if (v >= 0) std::cout << "+";
    std::cout << v << ")\n";
}

void Game::cmdApply(const std::string& itemName)//finds item in inventory, applies its trait effect to player stats, then removes it from inventory
{
    Item item;
    if (!player.getInventory().getItemByName(itemName, item))
    {
        std::cout << "You don't have '" << itemName << "'.\n";
        return;
    }
    
    //apply item effect based on trait type
    if (item.getTraitType() == Trait_Bankroll) player.addBankroll(item.getTraitValue());
    else if (item.getTraitType() == Trait_Luck) player.addLuck(item.getTraitValue());
    else if (item.getTraitType() == Trait_HouseEdge) player.addHouseEdge(item.getTraitValue());

    player.getInventory().removeItemByName(itemName);//remove item after applying

    std::cout << "You applied '" << itemName << "'.\n";
}

void Game::cmdPlay()
{
    //advances game state
    roundNumber++;

    int result = 0;

    if (currentGame == Game_Blackjack)
    {
        result = playBlackjackRound(player.getLuck(), player.getHouseEdge());
    }

    else if (currentGame == Game_Roulette)
    {
        std::cout << "\nRoulette is coming soon!\n";
        result = 0;
    }
    
    else if (currentGame == Game_Poker)
    {
        std::cout << "\nPoker is coming soon!\n";
        result = 0;
    }
    
    player.addBankroll(result);

    if (player.getBankroll() <=0)
    {
        std::cout << "You are out of money! Game Over.\n";
        std::exit(0);//end game if player goes bankrupt
    }

    if (result > 0)
    winStreak++;
    else if (result < 0)
    winStreak = 0;

    //displays updated game state after the round
    std::cout << "Round Number: " << roundNumber << "\n";
    std::cout << "Win Streak: " << winStreak << "\n";
    std::cout << "Bankroll: $" << player.getBankroll() << "\n";
}    

void Game::cmdShop() const{
    std::cout << "\n=== Shop ===\n";
    std::cout << "Your Bankroll: $" << player.getBankroll() << "\n";
    std::cout << "Use: buy <item>\n\n";

    for (int i = 0; i < Item_Count; i++)
    {
        std::cout << itemList[i].getName()
        << " - $" << itemPrice[i]
        << " | " << traitTypeToString(itemList[i].getTraitType()) << " ("
        << (itemList[i].getTraitValue() >= 0 ? "+" : "")
        << itemList[i].getTraitValue()
        << ")\n";
    }
}

void Game::cmdBuy(const std::string& itemName)
{
    int index = -1;

    for (int i = 0; i < Item_Count; i++)
    {
        if (itemList[i].getName() == itemName)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        std::cout << "Item '" << itemName << "' not found in shop.\n";
        return;
    }

    int cost = itemPrice[index];

    if (player.getBankroll() < cost)
    {
        std::cout << "You don't have enough money to buy '" << itemName << "'.\n";
        return;
    }

   if (!player.getInventory().addItem(itemList[index]))
   {
       std::cout << "Your inventory is full. Cannot buy '" << itemName << "'.\n";
       return;
   }
   
   player.addBankroll(-cost);

   std::cout << "You bought '" << itemName << "' for $" << cost << ".\n";
   std::cout << "Remaining Bankroll: $" << player.getBankroll() << "\n";
}   

void Game::cmdGames() const
{
    std::cout << "\n=== Available Games ===\n";
    std::cout << "blackjack\n";
    std::cout << "roulette (Coming Soon)\n";
    std::cout << "poker (Coming Soon)\n";
    std::cout << "Use: switch <game>\n";
}

void Game::cmdSwitch(const std::string& gameName)
{
    if (gameName == "blackjack")
    {
        currentGame = Game_Blackjack;
        std::cout << "Switched to Blackjack.\n";
    }
    else if (gameName == "roulette")
    {
        currentGame = Game_Roulette;
        std::cout << "Switched to Roulette. (coming soon)\n";
    }
    else if (gameName == "poker")
    {
        currentGame = Game_Poker;
        std::cout << "Switched to Poker. (coming soon)\n";
    }
    else
    {
        std::cout << "Game '" << gameName << "' not recognized.\n";
        std::cout << "Type 'games' to see available games.\n";
    }
}