//Game.cpp 
//Implements the Game class including command handling, gameplay rounds, and shop purchases

#include <iostream>
#include <string>
#include <cstdlib>
#include "Game.hpp"
#include "Blackjack.hpp"

//Converts TraitType enum value into readable string for printing item descriptions and shop listings
static std::string traitTypeToString(TraitType t)//placement here since it's only used in Game.cpp to print trait types
{
    if (t == Trait_Bankroll) return "Bankroll";
    if (t == Trait_Luck) return "Luck";
    return "House Edge";
}

Game::Game()
{
    roundNumber = 0;//total rounds played
    winStreak = 0;//consecutive wins

    currentGame = Game_Blackjack;//default to blackjack, other games can be added later

    //initialize items available in the shop
    //Each item stores name, description, trait type, and trait value
    //Bankroll items
    itemList[0] = Item("chips50", "A stack of chips worth fifty dollars.", Trait_Bankroll, 50);
    itemList[1] = Item("chips100", "A stack of chips worth one hundred dollars.", Trait_Bankroll, 100);
    itemList[2] = Item("chips200", "A stack of chips worth two hundred dollars.", Trait_Bankroll, 200);
    itemList[3] = Item("vaultcoupon", "A coupon redeemable for cash at the cage.", Trait_Bankroll, 300);
    
    //Luck items
    itemList[4] = Item("luckyshirt", "A shirt that makes you feel unbeatable.", Trait_Luck, 1);
    itemList[5] = Item("rabbitfoot", "A rabbit's foot that brings good luck to the holder.", Trait_Luck, 1);
    itemList[6] = Item("goldbracelet", "A gold bracelet that seems to shimmer with an otherworldly light.", Trait_Luck, 2);
    
    //House Edge Reducers (Beneficial for player)
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

void Game::setup()//setup runs once at start, asks for player name and archetype, then loads starting stats and inventory
{
    std::string name;
    int choice;

    std::cout <<"Enter your name: ";
    std::cin >>name;

    std::cout <<"\nChoose your player type:\n";
    std::cout << "1) High Roller (Bankroll 300, Luck 1)\n";
    std::cout << "2) Card Shark (Bankroll 200, Luck 3)\n";
    std::cout << "3) Lucky Newbie (Bankroll 100, Luck 6)\n";
    std::cout << "Enter choice (1-3): ";
    std::cin >> choice;

    if (choice < 1 || choice > 3) //Input validation: if player enters invalid choice, defaults to Lucky Newbie
    {
        choice = 3;
    }

    player.initialize(name, (PlayerType)choice);//Initialize player stats based on chosen archetype

    //starter inventory: gives player a small bankroll boost and starter luck and house edge reducer at beginning of game
    player.getInventory().addItem(itemList[0]);//chips50
    player.getInventory().addItem(itemList[4]);//luckyshirt
    player.getInventory().addItem(itemList[7]);//cardguide

    std::cout << "\nType 'help' to see available commands.\n";
}

void Game::showHelp() const
{
    
    //Prints a list of commands the player can type into the console 
    std::cout << "\n=== Available Commands ===\n";
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

void Game::cmdProfile() const//outputs player info and game progress info
{
    player.showProfile();
    std::cout << "Round Number: " << roundNumber << "\n";
    std::cout << "Win Streak: " << winStreak << "\n";
}

void Game::cmdInventory() const//displays player inventory contents
{
    player.getInventory().display();
}

void Game::cmdInspect(const std::string& itemName) const//displays item's description and trait details if player owns the item
{
    Item item;
    if (!player.getInventory().getItemByName(itemName, item))//returns true if item found, otherwise false
    {
        std::cout << "You don't have '" << itemName << "'.\n";
        return;
    }

    //print trait type and signed value
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
    if (!player.getInventory().getItemByName(itemName, item))//checks if player owns the item before applying it
    {
        std::cout << "You don't have '" << itemName << "'.\n";
        return;
    }
    
    //apply item's trait effect to player's stats
    if (item.getTraitType() == Trait_Bankroll) player.addBankroll(item.getTraitValue());
    else if (item.getTraitType() == Trait_Luck) player.addLuck(item.getTraitValue());
    else if (item.getTraitType() == Trait_HouseEdge) player.addHouseEdge(item.getTraitValue());

    player.getInventory().removeItemByName(itemName);//remove item after applying (consumable)

    std::cout << "You applied '" << itemName << "'.\n";
}

void Game::cmdPlay()
{
    //Player plays one round of the currently active game, then updates game state variables based on the result
    roundNumber++;

    int result = 0;//bankroll change for the round(+50 for win, -50 for loss, 0 for push)

    //Determine which game is currently active
    if (currentGame == Game_Blackjack)
    {
        result = playBlackjackRound(player.getLuck(), player.getHouseEdge());//blackjack round uses luck and house edge to modify win/push probability
    }

    else 
    {
        //placeholder for future games
        if (currentGame == Game_Roulette) std::cout << "\nRoulette is coming soon!\n";
        else if (currentGame == Game_Poker) std::cout << "\nPoker is coming soon!\n";

        result = 0;//no change to bankroll since other games aren't implemented yet
    }
    
    //update player bankroll based on game result
    player.addBankroll(result);

    //If bankroll hits 0, end the game with a game over message
    if (player.getBankroll() <=0)
    {
        std::cout << "You are out of money! Game Over.\n";
        std::exit(0);
    }

    //update win streak: if player won the round, increase win streak by 1, if they lost reset win streak to 0, if push leave win streak unchanged
    if (result > 0) winStreak++;
    else if (result < 0) winStreak = 0;
    
    //displays updated game state after the round
    std::cout << "Round Number: " << roundNumber << "\n";
    std::cout << "Win Streak: " << winStreak << "\n";
    std::cout << "Bankroll: $" << player.getBankroll() << "\n";
}    

void Game::cmdShop() const
{
    //Display every item available in the shop along with price and trait effect
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
    int index = -1;//search shop item list to find index of requested item

    for (int i = 0; i < Item_Count; i++)
    {
        if (itemList[i].getName() == itemName)
        {
            index = i;
            break;
        }
    }

    if (index == -1)//if item doesnt exist in the shop, abort
    {
        std::cout << "Item '" << itemName << "' not found in shop.\n";
        return;
    }

    int cost = itemPrice[index];

    if (player.getBankroll() < cost)//checks player bankroll to see if player can afford the item
    {
        std::cout << "You don't have enough money to buy '" << itemName << "'.\n";
        return;
    }

   if (!player.getInventory().addItem(itemList[index]))//checks whether item can be purchased if inventory space is available
   {
       std::cout << "Your inventory is full. Cannot buy '" << itemName << "'.\n";
       return;
   }
   
   player.addBankroll(-cost);//deduct item cost from player bankroll

   std::cout << "You bought '" << itemName << "' for $" << cost << ".\n";
   std::cout << "Remaining Bankroll: $" << player.getBankroll() << "\n";
}   

void Game::cmdGames() const//displays available casino games and how to switch
{
    std::cout << "\n=== Available Games ===\n";
    std::cout << "blackjack\n";
    std::cout << "roulette (Coming Soon)\n";
    std::cout << "poker (Coming Soon)\n";
    std::cout << "Use: switch <game>\n";
}

void Game::cmdSwitch(const std::string& gameName)
{
    //changes currently active game 
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