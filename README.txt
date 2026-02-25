Stack the Odds
-A Modular Console Casino Game Built in C++

Game Concept
-In Stack the Odds, the player enters a casino that is being rennovated. 
-The concept of the game revolves around modifying probability by collecting stat-altering items.

-The items the player can collect directly affect their:
*Bankroll
*House Edge
*Luck

-Wihin the casino, the player can: 

*Choose a player archetype 
*Purchase and equip stat-altering items
*Play casino games
*Switch between games
*Manage a Bankroll*

Player Archetypes
- At the start of the game, the player must choose an archetype. This archetype directly affects the player's stats. 

*Bankroll = Player's money
*House Edge = Decreases win probability (lower is better)
*Luck = Increasing win probability

Archetype           Bankrol             House Edge          Luck
__________________________________________________________________
*High Roller         1200                   5                1
*Card Shark          900                    3                3
*Lucky Newbie        1000                   6                6

Item Database (10 Items)
-Each item has:
*Name
*Description
*Trait type
*Trait value
*Shop price

Bankroll Items:
Item:                   Effect:
*chips50                +50 bankroll
*chips100               +100 bankroll
*chips200               +200 bankroll
vaultcoupon             +300 bankroll

House Edge Items:
Item:                   Effect:
*cardguide              -1 house edge
*vipband                -1 house edge
*pitbossfavor           -2 house edge

Luck Items:
Item:                   Effect:
*luckyshirt             +1 luck
*rabbitfoot             +1 luck
*goldbracelet           +2 luck

Inventory System
-The player has an inventory that supports:
*Add item
*Remove item
*Search by Name
*Display contents

-Additionally, the player can store up to 10 unique items during gameplay


