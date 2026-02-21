#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/questions.hpp"

int readInt()
{
    int value;
    std::cin >> value;
    return value;
}

static void addMoney(int *money, int amount)
{
    *money = *money + amount;
}

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
        std::cout << "Please enter your choice (1-4): ";
        int choice = readInt();
        
        if (choice >= 1 && choice <= 4)
        {    
        return choice;
        }
            std::cout << "Invalid choice. Please try again.\n";
    }
}    
//Cards & Shoe
int getRank(int card)
{
    return (card % 13) + 1;
}

int getSuit(int card)
{
    return card / 13;
}

int cardBaseValue(int card)
{
    int r = getRank(card);

    if (r >=2 && r <= 10) return r;
    if (r >= 11 && r <= 13) return 10;
        return 11; // Ace
}

void buildShoe(int shoe[], int shoeSize, int numDecks)
{
    int nextSlot = 0;

    for (int d = 0; d < numDecks; d++)
    {
        for (int c = 0; c < 52; c++)
        {
            if (nextSlot < shoeSize)
            {
                shoe[nextSlot] = c;
                nextSlot++;
            }
        }
    }
}

void shuffleShoe(int shoe[], int shoeSize)
{
    for (int i = shoeSize - 1; i > 0; i--)
    {
        int j = std::rand() % (i + 1);
        int temp = shoe[i];
        shoe[i] = shoe[j];
        shoe[j] = temp;
    }
}

int drawCard(int shoe[], int shoeSize, int &shoePos, int numDecks)
{
    //rebuild and shuffle shoe if we've reached the end
    if (shoePos >= shoeSize)
    {
        buildShoe(shoe, shoeSize, numDecks);
        shuffleShoe(shoe, shoeSize);
        shoePos = 0;
    }
    
    int card = shoe[shoePos];
    shoePos++;
    return card;
}

//Hand evaluation
int handValue(const int hand[], int count)
{
   int total = 0;
   int AceCount = 0;

   for (int i=0; i < count; i++)
   {
        total += cardBaseValue(hand[i]);
        if (getRank(hand[i]) == 1)
        {
            AceCount++;
        }
   }
   // Adjust for aces if total is over 21
   while (total > 21 && AceCount > 0)
   {
       total -= 10;
       AceCount--;
   }
   return total;
}
bool isBust(const int hand[], int count)
{
    if (handValue(hand, count) > 21) return true;
    return false;
}

bool isBlackjack(const int hand[], int count)
{
    if (count == 2 && handValue(hand, count) == 21) return true;
    return false;
}

bool canSplitHand(const int hand[], int count)
{
    if (count != 2) return false;

    int r1 = getRank(hand[0]);
    int r2 = getRank(hand[1]);

    if (r1 == r2) return true;
    return false;
}

bool canDoubleDown( const int hand[], int count)
{
    if (count == 2) return true;
    return false;
}

void resetHand(int hand[], int &count, int maxSize)
{
    count = 0;
    for (int i = 0; i < maxSize; i++)
    {
        hand[i] = -1;
    }
}

//Display
void printCard(int card)
{
    int r = getRank(card);
    int s = getSuit(card);

    //Rank
    if (r == 1) std::cout << "A";
    else if (r == 11) std::cout << "J";
    else if (r == 12) std::cout << "Q";
    else if (r == 13) std::cout << "K";
    else std::cout << r;

    //Suit
    if (s==0) std::cout << "C";
    else if (s == 1) std::cout << "D";
    else if (s == 2) std::cout << "H";
    else std::cout << "S";
}

void printHand(const std::string &label, const int hand[], int count, bool hideFirstCard)
{
    std::cout << label << ": ";

    for (int i = 0; i < count; i++)
    {
        if (hideFirstCard == true && i == 0)
        {
            std::cout << "[??] ";
        }
        else
        {
            std::cout << "[";
            printCard(hand[i]);
            std::cout << "] ";
        }
    }
    if (hideFirstCard == false)
    {
        std::cout << "(Total: " << handValue(hand, count) << ")";
    }
    std::cout << "\n";
}

void printHands(const std::string &playerName, const int playerHand[], int playerCount, const int dealerHand[], int dealerCount, bool hideDealerFirst)

{
    std::cout << "\n";
    printHand("Dealer", dealerHand, dealerCount, hideDealerFirst);
    printHand(playerName, playerHand, playerCount, false);
    std::cout << "\n";
}

//Deal and turn helpers
void dealStartingHands(int shoe[], int shoeSize, int &shoePos, int numDecks, int playerHand[], int &playerCount, int dealerHand[], int &dealerCount)
{
    playerHand[playerCount] = drawCard(shoe, shoeSize, shoePos,numDecks);
    playerCount++;

    dealerHand[dealerCount] = drawCard(shoe, shoeSize, shoePos, numDecks);
    dealerCount++;

    playerHand[playerCount] = drawCard(shoe, shoeSize, shoePos, numDecks);
    playerCount++;

    dealerHand[dealerCount] = drawCard(shoe, shoeSize, shoePos, numDecks);
    dealerCount++;
}

//1=Hit, 2=Stand, 3=Double Down, 4=Split, 5=Quit
int getPlayerDecision(bool allowDoubleDown, bool allowSplit)

{
    while (true)
    {
        std::cout << "Choose: 1=Hit 2=Stand";

        if (allowDoubleDown == true)
        {
            std::cout << " 3=Double Down";
        }

        if(allowSplit == true)
        {
            std::cout << " 4=Split";
        }

        std::cout << " 5=Quit\n";
        std::cout << "Enter choice: ";

        int choice = readInt();

        if (choice == 1) return 1;
        if (choice == 2) return 2;
        if (choice == 3 && allowDoubleDown == true) return 3;
        if (choice == 4 && allowSplit == true) return 4;
        if (choice == 5) return 5;

        std::cout << "Invalid choice. Please try again.\n";
    }
}

void playerTurn(int shoe[], int shoeSize, int &shoePos, int numDecks, int playerHand[], int &playerCount, const int dealerHand[], int dealerCount, const std::string &playerName, int &bankroll, int &bet, int fixedBet, bool allowSplitFirstDecision, bool &quitRound)

{
    bool firstDecision = true;
    while (true)
    {
        printHands(playerName, playerHand, playerCount, dealerHand, dealerCount, true);

        if (isBust(playerHand, playerCount) == true)
    
        {
        return;
        }

        bool allowDouble = canDoubleDown(playerHand, playerCount);
        bool allowSplit = false;
        
        if (firstDecision == true)
        {
            allowSplit = allowSplitFirstDecision;
        }
        
        //Need money available to double down (adds fixedBet)
        if (allowDouble == true && bankroll < bet + fixedBet)
        {
            allowDouble = false;
        }

        int decision = getPlayerDecision(allowDouble, allowSplit);
        if (decision == 5)
        {
            quitRound = true;
            return;
        }
        else if (decision == 1)
        {
            playerHand[playerCount] = drawCard(shoe, shoeSize, shoePos, numDecks);
            playerCount++;
        }
        else if (decision == 2)
        {
            return;
        }
        else if (decision == 3)
        {
            //Double down: pay extra fixed bet, draw a car, and stand
            addMoney(&bankroll, -fixedBet);
            bet += fixedBet;

            std::cout << "Double Down!\n";

            playerHand[playerCount] = drawCard(shoe, shoeSize, shoePos, numDecks);
            playerCount++;
            return;
        }
        else
        {
        return;
        }

        firstDecision = false;
    }
}

void dealerTurn(int shoe[], int shoeSize, int &shoePos, int numDecks, int dealerHand[], int &dealerCount)
{
    while (handValue(dealerHand, dealerCount) < 17)
    {
        dealerHand[dealerCount] = drawCard(shoe, shoeSize, shoePos, numDecks);
        dealerCount++;
    }
}

//Round Controller (betting, bonus, split, quit penalty)

bool playBlackjackRound(int shoe[], int shoeSize, int &shoePos, int numDecks, const std::string &playerName, int &bankroll)

{
    const int fixedBet = 50;
    const int quitPenalty = 50;
    const int Max_Hand = 12;

    if (bankroll < fixedBet)
    {
        std::cout << "\nNot enough money to bet $" << fixedBet << ".\n";
        return true; //return player to menu
    }

    //Base bet for hand 1

    addMoney(&bankroll, -fixedBet);

    int bet1 = fixedBet;
    int bet2 = 0;

    int dealerHand[Max_Hand];
    int dealerCount = 0;

    int hand1[Max_Hand];
    int hand2[Max_Hand];
    int count1 = 0;
    int count2 = 0;

    resetHand(dealerHand, dealerCount, Max_Hand);
    resetHand(hand1, count1, Max_Hand);
    resetHand(hand2, count2, Max_Hand);

    dealStartingHands(shoe, shoeSize, shoePos, numDecks, hand1, count1, dealerHand, dealerCount);

    //Check for immediate blackjack
    bool pBJ = isBlackjack(hand1, count1);
    bool dBJ = isBlackjack(dealerHand, dealerCount);

    if (pBJ == true || dBJ == true)
    {
        printHands(playerName, hand1, count1, dealerHand, dealerCount, false);

        if (pBJ == true && dBJ == true)
        {
            std::cout << "Push! Both player and dealer have Blackjack.\n";
            addMoney(&bankroll, bet1); //return bet
        }
        else if (pBJ == true)
        {
            std::cout << "Blackjack Bonus!\n";

            int bonus = (bet1 * 3) / 2; //1.5x payout
            int totalReturn = bet1 + bonus;
            addMoney(&bankroll, totalReturn);
        }
        else
        {
            std::cout << "Dealer has Blackjack. You lose.\n";
        }

        std::cout << "Bankroll: $" << bankroll << "\n";
        return false;
    }
    
    //Split option only offered on first decision (extra bet money required)
    bool allowSplit = canSplitHand(hand1, count1);
    if (allowSplit == true && bankroll < fixedBet)
    {
        allowSplit = false;
    }

    //First decision includes split/double/quit
    printHands(playerName, hand1, count1, dealerHand, dealerCount, true);

    bool allowDouble = true;
    if (bankroll < fixedBet) allowDouble = false;
    
    int firstChoice = getPlayerDecision(allowDouble, allowSplit);

    if (firstChoice ==5)
    {
        std::cout << "Quit mid-round.\n";
        std::cout << "Penalty: -$" << quitPenalty << "\n";

        addMoney(&bankroll, -quitPenalty);
        if (bankroll < 0) bankroll = 0;

        return true; //return player to menu
    }

    bool didSplit = false;

    //Handle split immediately
    if (firstChoice == 4 && allowSplit == true)
    {
        addMoney(&bankroll, -fixedBet);
        bet2 = fixedBet;

        //Move second card to new hand
        hand2[count2] = hand1[1];
        count2++;
        count1 = 1;

        //Draw a card for each hand
        hand1[count1] = drawCard(shoe, shoeSize, shoePos, numDecks);
        count1++;

        hand2[count2] = drawCard(shoe, shoeSize, shoePos, numDecks);
        count2++;

        didSplit = true;
        std::cout << "Split!\n";
    }
    else if (firstChoice == 3 && allowDouble == true)
    {
        //Double down right away
        addMoney(&bankroll, -fixedBet);
        bet1 += fixedBet;

                std::cout << "Double Down!\n";

                hand1[count1] = drawCard(shoe, shoeSize, shoePos, numDecks);
                count1++;
    }
    else if (firstChoice == 1)
    {
        //Hit
        hand1[count1] = drawCard(shoe, shoeSize, shoePos, numDecks);
        count1++;
    }
    else
    {
        //Stand - do nothing
    }
    
    bool quitRound = false;

    //Player plays hand if they didn't split
    if (didSplit == false)
    {
        //If player doubles, stand automatically
        if (firstChoice != 3)
        {
            playerTurn(shoe, shoeSize, shoePos, numDecks, hand1, count1, dealerHand, dealerCount, playerName, bankroll, bet1, fixedBet, false, quitRound);
        }

        if (quitRound == true)
        {
            std::cout << "Quit mid-round.\n";
            std::cout << "Penalty: -$" << quitPenalty << "\n";

            addMoney(&bankroll, -quitPenalty);
            if (bankroll < 0) bankroll = 0;

            return true; //return player to menu after penalty
        }
    }
else
{
    //Player plays first hand
    playerTurn(shoe, shoeSize, shoePos, numDecks, hand1, count1, dealerHand, dealerCount, playerName + " (Hand 1)", bankroll, bet1, fixedBet, false, quitRound);

    if (quitRound == true)
    {
        std::cout << "Quit mid-round.\n";
        std::cout << "Penalty: -$" << quitPenalty << "\n";

        addMoney(&bankroll, -quitPenalty);
        if (bankroll < 0) bankroll = 0;

        return true; 
    }

    //Player plays second hand
    playerTurn(shoe, shoeSize, shoePos, numDecks, hand2, count2, dealerHand, dealerCount, playerName + " (Hand 2)", bankroll, bet2, fixedBet, false, quitRound);

    if (quitRound == true)
    {
        std::cout << "Quit mid-round.\n";
        std::cout << "Penalty: -$" << quitPenalty << "\n";

        addMoney(&bankroll, -quitPenalty);
        if (bankroll < 0) bankroll = 0;

        return true; 
    }
}

//Dealer plays if at least one player hand is still active
bool bust1 = isBust(hand1, count1);
bool bust2 = true;
if (didSplit == true)
{
    bust2 = isBust(hand2, count2);
}
if (bust1 == false || (didSplit == true && bust2 == false))
{
    dealerTurn(shoe, shoeSize, shoePos, numDecks, dealerHand, dealerCount);
}

//Show final hands
std::cout << "\n===== Final =====\n";
if (didSplit == false)
{
    dealerTurn(shoe, shoeSize, shoePos, numDecks, dealerHand, dealerCount);
}
else
{
    printHand("Dealer", dealerHand, dealerCount, false);
    printHand(playerName + " (Hand 1)", hand1, count1, false);
    printHand(playerName + " (Hand 2)", hand2, count2, false);
    std::cout << "\n";
}

//Profit per hand
int dealerVal = handValue(dealerHand, dealerCount);

//Hand 1 outcome
int profit1 = 0;
int p1 = handValue(hand1, count1);

if (p1 > 21)
{
    profit1 = -bet1;
}
else if (dealerVal > 21)
{
    profit1 = bet1;
}
else if (p1 > dealerVal)
{
    profit1 = bet1;
}
else if (p1 < dealerVal)
{
    profit1 = -bet1;
}
else
{
    profit1 = 0;
}

//Apply payout to bankroll
if (profit1 > 0)
{
    addMoney(&bankroll, bet1 + profit1);//return bet + profit
}
else if (profit1 == 0)
{
    std::cout << "Hand Profit: ";
    if (profit1 >= 0) std::cout << "+$" << profit1 << "\n";
    else std::cout << "-$" << (-profit1) << "\n";
}
else
{
    //Hand 2 outcome
    int profit2 = 0;
    int p2 = handValue(hand2, count2);

    if (p2 > 21)
    {
        profit2 = -bet2;
    }
    else if (dealerVal > 21)
    {
        profit2 = bet2;
    }
    else if (p2 > dealerVal)
    {
        profit2 = bet2;
    }
    else if (p2 < dealerVal)
    {
        profit2 = -bet2;
    }
    else
    {
        profit2 = 0;
    }
    if (profit2 > 0)
    {
        addMoney(&bankroll, bet2 + profit2);//return bet + profit
    }
    else if (profit2 == 0)
    {
       addMoney(&bankroll, bet2);//return bet
    }

    std::cout << "Hand 1 Profit: ";
    if (profit1 >= 0) std::cout << "+$" << profit1 << "\n";
    else std::cout << "-$" << (-profit1) << "\n";

    std::cout << "Hand 2 Profit: ";
    if (profit2 >= 0) std::cout << "+$" << profit2 << "\n";
    else std::cout << "-$" << (-profit2) << "\n";

    int totalProfit = profit1 + profit2;
    std::cout << "Total Profit: ";
    if (totalProfit >= 0) std::cout << "+$" << totalProfit << "\n";
    else std::cout << "-$" << (-totalProfit) << "\n";
}

std::cout << "Bankroll: $" << bankroll << "\n";
return false;
}

//Start Blackjack 
void startBlackjack(int &bankroll)
{
    std::string playerName;
    std::cout << "\nEnter your name: ";
    std::cin >> playerName;

    const int numDecks = 6;
    const int shoeSize = 52 * numDecks;

    int shoe[52 * 6];
    int shoePos = 0;

    buildShoe(shoe, shoeSize, numDecks);
    shuffleShoe(shoe, shoeSize);

    std::cout << "\nWelcome, " << playerName << "!\n";
    std::cout << "Bankroll: $:" << bankroll << " | Fixed bet: $50\n";

    bool keepPlaying = true;

    while (keepPlaying == true)
    {
        bool quitToMenu = playBlackjackRound(shoe, shoeSize, shoePos, numDecks, playerName, bankroll);

        if (quitToMenu == true)
        {
            std::cout << "Returning to main menu...\n";
            return;
        }

        int again;
        while (true)
        {
            std::cout << "\nPlay another round? (1=Yes, 2=No): ";
            again = readInt();
            if (again == 1 || again == 2)
            {
                break;
            }
            std::cout << "Invalid choice. Please try again.\n";
        }

        if (again == 2)
        {
            keepPlaying = false;
        }
        
        if (bankroll < 50)
        {
            std::cout << "\nNot enough money to continue playing Blackjack. Returning to main menu.\n";
            keepPlaying = false;
        }
    }
    std::cout << "Returning to main menu...\n";
}
