//main.cpp
//Handles the main command loop 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Game.hpp"

int main()
{
    //Seed random number generator 
    std::srand((unsigned)std::time(0));

    Game game;
    game.setup();//Initializes player and starting items

    bool running = true;

    while (running)
    {
        std::cout << "\n> ";

        std::string command;//read user command input
        std::cin >> command;

        if (command == "help")
        {
            game.showHelp();
        }
        else if (command == "profile")
        {
            game.cmdProfile();
        }
        else if (command == "inventory")
        {
            game.cmdInventory();   
        }
        else if (command == "inspect")//inspect requires argument: item name
        {
            std::string arg;

            if (std::cin >> arg)
            {
                  game.cmdInspect(arg);
            }
            else
            {
              std::cout << "Usage: inspect <item>\n";
            }
        }

        else if (command == "apply")//apply requires argument: item name
        {
            std::string arg;

            if (std::cin >> arg)
            {
                game.cmdApply(arg);
            }

            else
            {
                std::cout << "Usage: apply <item>\n";
            }
        }

        else if (command == "shop")
        {
            game.cmdShop();
        }

        else if (command == "buy")//buy requires argument: item name
        {
            std::string arg;

            if (std::cin >> arg)
            {
                game.cmdBuy(arg);
            }

            else
            {
                std::cout << "Usage: buy <item>\n";
            }
        }

        else if(command == "games")
        {
            game.cmdGames();
        }

        else if (command == "switch")//switch requires argument: game name
        {
            std::string arg;
            
            if (std::cin >> arg)
            {
                game.cmdSwitch(arg); 
            }

            else
            {
                std::cout << "Usage: switch <game>\n";
            }
        }

        else if (command == "play")
        {
            game.cmdPlay();
        }

        else if (command == "quit")
        {
            running = false;
        }

        else 
        {
            std::cout << "Unknown command. Type 'help' .\n";
        }
    }

    std::cout << "\nGoodbye!\n";
    return 0;
}