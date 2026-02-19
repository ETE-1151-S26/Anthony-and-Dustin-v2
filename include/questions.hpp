#pragma once
#include <string>

//Display casino menu
void showMainMenu();

//Reads and validates user input for menu choice
int getMenuChoice();

//Starts blackjack game
void startBlackjack();

//Functions for managing shoe (multiple decks) 
void buildShoe(int shoe[], int shoeSize, int numDecks);
void shuffleShoe(int shoe[], int shoeSize);
int drawCard(int shoe[], int shoeSize, int* shoePos, int numDecks);

//Functions for card management
int getRank(int card);
int getSuit(int card);
int cardBaseValue(int card);

//Functions to evaluate hand 
int handValue(const int hand[], int count);
bool isBust(const int hand[], int count);
bool isBlackjack(const int hand[], int count);
void resetHand(int hand[], int* count, int maxSize);
bool canSplitHand(const int hand[], int count);
bool canDoubleDown(const int hand[], int count);

//Functions for displaying cards and hands to player
void printCard(int card);
void printHand(const std::string &label, const int hand[], int count, bool hideFirstCard);
void printHands(const std::string &playerName, const int playerHand[], int playerCount, const int dealerHand[], int dealerCount, bool hideDealerFirst);

//Functions to manage player and dealer turns
void dealStartingHands(int shoe[], int shoeSize, int* shoePos, int numDecks, int playerHand[], int* playerCount, int dealerHand[], int* dealerCount);
int getPlayerDecision(bool allowDoubleDown, bool allowSplit);//Returns 1=Hit, 2=Stand, 3=Double Down, 4=Split
void playerTurn(int shoe[], int shoeSize, int* shoePos, int numDecks, int playerHand[], int* playerCount, const int dealerHand[], int dealerCount, const std::string &playerName);
void dealerTurn(int shoe[], int shoeSize, int* shoePos, int numDecks, int dealerHand[], int* dealerCount);
void playBlackjackRound(int shoe[], int shoeSize, int* shoePos, int numDecks, const std::string &playerName);

//Function for processing user input
int readInt();