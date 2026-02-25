Stack the Odds
-A Modular Console-Based Casino Game Built in C++

Game Concept
-In Stack the Odds, the player enters a casino that is being rennovated, with Blackjack being the only playable game at the moment. The gameplay revolves around manipulating probability by collecting stat-altering items that modify the player's attributes. The system was designed with the intention of simulating a scalable altered casino experience. Despite Blackjack being the only playable game, placeholders were set in the menu for Poker and Roulette to be added in the future. Players should strategically acquire items to "Stack the Odds" in their favor

Program Architecture and Design Decisions
-The program consists of core classes that help organize responsibilities.
 
 Core classes and Responsibilities:
 -Game: Controls overall game flow, command interpretation, state management, and interaction between systems.
 -Player: Stores player information, statistics, inventory, and archetype selection.
 -Blackjack: Implements a probability-based Blackjack game that calculates win, loss, and push outcomes.
 -Inventory: Manages a fixed size collection of item objects. Functions include add, display, search, and remove. 
 -Item: Contains all relevant information related to items such as name, description, trait type, and trait value.

 Design Decisions:
 -The purpose of file structure/design was to ensure organization between components of program as well as option to build upon standing structure. 
 *The Blackjack logic was purposely seperated to allow future expansion of casino games.
 *The command based loop within main.cpp allows for easy input parsing within the program. 
 
 Player Archetypes
- At the start of the game, the player must choose an archetype. The selected archetype directly affects the player's starting stats. 

 Definitions:
 *Bankroll = Player's money
 *House Edge = Decreases win probability (lower is better)
 *Luck = Increasing win probability

Archetype           Bankrol             House Edge          Luck
__________________________________________________________________
*High Roller         1200                   5                1
*Card Shark          900                    3                3
*Lucky Newbie        1000                   6                6

Item Database (10 Items)
-Each item has a:
 *Name
 *Description
 *Trait type
 *Trait value
 *Shop price

Bankroll Items:
Item:                Price:                 Effect:                     Description:
 *chips50             $50                   +50 bankroll               "A stack of chips worth fifty dollars."
 *chips100            $100                  +100 bankroll              "A stack of chips worth one hundred dollars."
 *chips200            $200                  +200 bankroll              "A stack of chips worth two hundred dollars."
 vaultcoupon          $300                  +300 bankroll              "A coupon redeemable for cash at the cage."

House Edge Items:
Item:               Price:                  Effect:                     Description:
 *cardguide          $80                   -1 house edge              "A guidebook that provides insights into card probabilities."
 *vipband            $90                   -1 house edge              "A VIP wristband that grants friendlier table rules."
 *pitbossfavor       $150                  -2 house edge              "A favor from the pit boss that lowers table pressure."

Luck Items:
Item:              Price:                  Effect:                     Description:
 *luckyshirt         $75                   +1 luck                    "A shirt that makes you feel unbeatable."
 *rabbitfoot         $60                   +1 luck                    "A rabbit's foot that brings good luck to the holder."
 *goldbracelet       $120                  +2 luck                    "A gold bracelet that seems to shimmer with an otherworldly light."

Inventory System
-The player inventory system stores 10 unique items that can be acquired through the casino's shop. If Inventory is full, the system prevents anymore purchases.

 Inventory features:
 *Add item
 *Remove item
 *Search by Name
 *Display contents

Shop System
-The casino's shop is the place where players can directly alter their chances
 
 Shop features:
 *View items list 
 *View item prices
 *View item trait effects
 *Purchase new items if funds & inventory space available
 *Prevent purchases if inventory is full

Blackjack System
-One of the casino's working games is currently Blackjack. Unlike traditional Blackjack (21), the current implementation uses probability as its core model. If player bankroll reaches 0, the game will end. Push chance is adjusted based on Luck and House Edge.

 Base Probabilities:
 *42% win chance
 *6% push chance
 *52% lose chance
 
 Constraints:
 *Minimum win chance: 5%
 *Maximum win chance: 90%

 Win Chance Probability Formula:
  winChance = 42 + luck - houseEdge

 Lose Chance = 100 - (winChance + pushChance)

 Payout Structure:
 *Win = +$50
 *Lose = -$50
 *Push = $0

 Modifiers:
 -House Edge:
            *decreases win chance
            *increases push chance
 -Luck:
      *decreases push chance
      *increases win chance

Game State Variables
-Within the game, the system will keep track of the player's:
 *Stats
 *Current game selection
 *Round Number 
 *Win streak
 *Bankroll

*Note* The system's command driven loop allows for the player to keep playing until deciding to quit or running out of money.

User manual 