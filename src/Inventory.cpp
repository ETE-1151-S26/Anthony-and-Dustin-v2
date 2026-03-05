//Inventory.cpp
//Implements inventory operations

#include <iostream>
#include "Inventory.hpp"

Inventory::Inventory()//initializes empty inventory
{
    count = 0;//start with empty inventory
}

int Inventory::getCount() const//returns current number of items in inventory
{
    return count;
}

int Inventory::getCapacity() const//returns max capacity of inventory
{
    return Capacity;
}

//adds an item to inventory if space available
//returns true if successful, false if inventory full
bool Inventory::addItem(const Item& item)
{
    if(count >= Capacity) return false;//check if there's space in inventory
    items[count] = item;//add item to next open slot
    count++;//increment item count
    return true;
}

//searches inventory for item with matching name
//if found, copies item to outItem and returns true; otherwise returns false
bool Inventory::getItemByName(const std::string& name, Item& outItem) const
{
    for (int i = 0; i < count; i++)//loop through valid items in inventory
    {
        if (items[i].getName() == name)//check for name match
        {
            outItem = items[i];//copy the found item to outItem parameter
            return true;
        }
    }
    return false;//no item with matching name found
}

//removes first item with matching name from inventory
//returns true if item was found and removed, false if no matching item found
bool Inventory::removeItemByName(const std::string& name)
{
    int index = -1;//will store location of item if found
    
    //search for item by name
    for (int i = 0; i < count; i++)
    {
        if (items[i].getName() == name)
        {
            index = i;//store where the item was found
            break;//stop searching once found
        }
    }
    if (index == -1) //if index is still -1, the item was not found
    return false;

    for (int i = index; i < count - 1; i++)//shift all items after the removed item down one slot to fill the gap
    {
        items[i] = items[i + 1];
    }
    count--;//reduce item count since one item was removed
    return true;
}

//displays inventory contents to the player
void Inventory::display() const
{
    std::cout << "\n=== Inventory (" << count << "/" << Capacity << ") ===\n";
    if (count == 0)//if inventory is empty, show message and exit
    {
        std::cout << "(empty)\n";
        return;
    }

    for (int i = 0; i < count; i++)//loop through and display each item in inventory
    {
        std::cout << "- " << items[i].getName() << " | ";
        
        //display trait type of the item
        if (items[i].getTraitType() == Trait_Bankroll) 
            std::cout << "Bankroll";
        else if (items[i].getTraitType() == Trait_Luck) 
            std::cout << "Luck";
        else 
            std::cout << "House Edge";

        //show numerical trait value with proper sign
        int v = items[i].getTraitValue();
        std::cout << " (";

        if (v >= 0) std::cout << "+";
            std::cout << v << ")\n";
    }
}