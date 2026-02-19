#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "../include/questions.hpp"

//Main Menu
void showMainMenu()
{
    std::cout << "\n======= Casino Menu =======\n";
    std::cout << "     Welcome to the Casino!\n";
    std::cout << "============================\n";
    std::cout << "1. Play Blackjack\n";
    std::cout << "2. Poker (Coming Soon)\n";
    std::cout << "3. Roulette (Coming Soon)\n";
    std::cout << "4. Exit\n";
}

int getMenuChoice()
{
    while (true)
    {
        std::cout << "Please enter your choice: ";
        int c = readInt();
        if (c >= 1 && c <= 4)
            return c;
        std::cout << "Invalid choice. Please try again.\n";
    }
}    