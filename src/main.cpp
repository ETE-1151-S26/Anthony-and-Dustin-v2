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
            std::cin >> arg;
            game.cmdInspect(arg);
        }
        else if (command == "apply")//apply requires argument: item name
        {
            std::string arg;
            std::cin >> arg;
            game.cmdApply(arg);
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