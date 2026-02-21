#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/questions.hpp"

int main()
{
    std::srand(std::time(0));//seed random number generator 
    
    int bankroll = 1000;//Shared bankroll for player casino games
    bool running = true;
   
    while (running == true)
    {
        showMainMenu();
        int choice = getMenuChoice();

        if (choice == 1)
        {
            startBlackjack(bankroll);
        }
        else if (choice == 2)
        {
            std::cout << "\nPoker (Coming Soon)\n";
        }
        else if (choice == 3)
        {
            std::cout << "\nRoulette (Coming Soon)\n";
        }
        else if (choice == 4)
        {
            running = false;
        }
    }

    std::cout << "\nThank you for visiting the Casino! Your final bankroll is: $" << bankroll << "\n";
    return 0;
}