#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Game.hpp"

int main()
{
    std::srand((unsigned)std::time(0));

    Game game;
    game.setup();//main game loop

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
            if (!(std::cin >> arg))
            {
                std::cin.clear();
                std::cout << "Usage: inspect <item>\n";
            }
            else
            {
                game.cmdInspect(arg);
            }
        }
        else if (command == "apply")//apply requires argument: item name
        {
            std::string arg;
            if (!(std::cin >> arg))
            {
                std::cin.clear();
                std::cout << "Usage: apply <item>\n";
            }
            else
            {
                game.cmdApply(arg);
            }
        }
        else if (command == "shop")
        {
            game.cmdShop();
        }
        else if (command == "buy")//buy requires argument: item name
        {
            std::string arg;
            if (!(std::cin >> arg))
            {
                std::cin.clear();
                std::cout << "Usage: buy <item>\n";
            }
            else
            {
                game.cmdBuy(arg);
            }
        }
        else if(command == "games")
        {
            game.cmdGames();
        }
        else if (command == "switch")//switch requires argument: game name
        {
            std::string arg;
            if (!(std::cin >> arg))
            {
                std::cin.clear();
                std::cout << "Usage: switch <game>\n";
            }
            else
            {
                game.cmdSwitch(arg);
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