#pragma once

// Blackjack game loic
//simulates a round of blackjack using probability instead of a full card system
//Player stats influence the chances of winning, losing, or pushing each round
//Luck increases win chance 
//House edge reduces win chance
//Return values for player bankroll:
//Player wins round: +50
//Player loses round: -50
//Push (tie): 0

int playBlackjackRound(int luck, int houseEdge);
