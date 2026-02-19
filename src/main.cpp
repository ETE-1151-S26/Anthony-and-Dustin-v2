#include <cstdlib>
#include <ctime>
#include "../include/questions.hpp"

int main()
{
    std::srand(std::time(0));//seed random number generator 
    startBlackjack();//Start the blackjack game

    return 0;
}