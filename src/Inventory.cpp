#include <iostream>
#include "Inventory.hpp"

Inventory::Inventory()
{
    count = 0;
}

int Inventory::getCount() const
{
    return count;
}

int Inventory::getCapacity() const
{
    return Capacity;
}

bool Inventory::addItem(const Item& item)
{
    if(count >= Capacity) return false;//If inventory full, do nothing
    items[count] = item;
    count++;
    return true;
}

bool Inventory::getItemByName(const std::string& name, Item& outItem) const
{
    for (int i = 0; i < count; i++)
    {
        if (items[i].getName() == name)
        {
            outItem = items[i];
            return true;
        }
    }
    return false;
}

bool Inventory::removeItemByName(const std::string& name)
{
    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (items[i].getName() == name)
        {
            index = i;
            break;
        }
    }
    if (index == -1) return false;

    for (int i = index; i < count - 1; i++)
    {
        items[i] = items[i + 1];
    }
    count--;
    return true;
}

void Inventory::display() const
{
    std::cout << "\n=== Inventory (" << count << "/" << Capacity << ") ===\n";
    if (count == 0)
    {
        std::cout << "(empty)\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        std::cout << "- " << items[i].getName() << " | ";
        
        //show trait type
        if (items[i].getTraitType() == Trait_Bankroll) std::cout << "Bankroll";
        else if (items[i].getTraitType() == Trait_Luck) std::cout << "Luck";
        else std::cout << "House Edge";

        //show signed trait value
        int v = items[i].getTraitValue();
        std::cout << " (";
        if (v >= 0) std::cout << "+";
        std::cout << v << ")\n";
    }
}