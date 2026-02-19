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
    While (true)
    {
        std::cout << "Please enter your choice: ";
        int choice = readInt();
        if (choice >= 1 && choice <= 4)
            return choice;
        std::cout << "Invalid choice. Please try again.\n";
    }
}    