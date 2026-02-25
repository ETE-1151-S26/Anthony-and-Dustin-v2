#include <iostream>
#include <cstdlib>
#include "Blackjack.hpp"

int playBlackjackRound(int luck, int houseEdge)
{
    const int betAmount = 50;

    std::cout << "\n=== Blackjack Round ===\n";

    //Base win chance = 42% (casino edge)
    int winChance = 42;

    //luck improves chance
    winChance += luck;

    //House edge reduces chance
    winChance -= houseEdge;

    if (winChance < 5) winChance = 5;
    if (winChance > 90) winChance = 90;

    //push chance (tie)
    int pushChance = 6;
    pushChance += (houseEdge / 2); //house edge increases push chance
    pushChance -= (luck / 3); //luck reduces push chance

    if (pushChance < 2) pushChance = 2;
    if (pushChance > 15) pushChance = 15;

    if (winChance + pushChance > 95)
    {
        pushChance = 95 - winChance;
        if (pushChance < 2) pushChance = 2;
    }

    //print chances so the player can see the impact of their stats
    std::cout << "Win chance: " << winChance << "%\n";
    std::cout << "Push chance: " << pushChance << "%\n";
    std::cout << "Lose chance: " << (100 - (winChance + pushChance)) << "%\n";

    int roll = std::rand() % 100;

     if (roll < winChance)
    {
        std::cout << "You win the blackjack hand! +$" << betAmount << "\n";
        return betAmount;
    }
    else if (roll < winChance + pushChance)
    {
        std::cout << "It's a push! No money won or lost.\n";
        return 0;
    }
    else
    {
        std::cout << "You lose the blackjack hand. -$" << betAmount << "\n";
        return -betAmount;
    }
}
