//Blackjack.cpp
//Implements the Blackjack game 
//Blackjack is probability based
//Plays a single round and returns bankroll change for that round

#include <iostream>
#include <cstdlib>
#include "Blackjack.hpp"

int playBlackjackRound(int luck, int houseEdge)
{
    const int betAmount = 50;

    //Base probabilities (percent)
    const int BaseWinChance = 42;
    const int BasePushChance = 6;

    //Clamp limits (percent)
    const int MinWinChance = 5;
    const int MaxWinChance = 90;

    const int MinPushChance = 2;
    const int MaxPushChance = 15;

    const int MaxTotalChance = 95;//win + push can't exceed this to ensure there's always a chance to lose

    std::cout << "\n=== Blackjack Round ===\n";

    int winChance = BaseWinChance;
    winChance += luck;
    winChance -= houseEdge;

    //Clamp win chance to limits
    if (winChance < MinWinChance) winChance = MinWinChance;
    if (winChance > MaxWinChance) winChance = MaxWinChance;

    //push chance (tie)
    int pushChance = BasePushChance;
    pushChance += (houseEdge / 2); //house edge increases push chance
    pushChance -= (luck / 3); //luck reduces push chance

    if (pushChance < MinPushChance) pushChance = MinPushChance;
    if (pushChance > MaxPushChance) pushChance = MaxPushChance;

    if (winChance + pushChance > MaxTotalChance)
    {
        pushChance = MaxTotalChance - winChance;
        if (pushChance < MinPushChance) pushChance = MinPushChance;
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
