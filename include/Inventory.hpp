#pragma once
#include <string>
#include "Item.hpp"

class Inventory
{
private:
    static const int Capacity = 10;
    Item items[Capacity];
    int count;

public:
    Inventory();

    bool addItem(const Item& item);
    bool removeItemByName(const std::string& name);
    bool getItemByName(const std::string& name, Item& outItem) const;

    void display() const;

    int getCount() const;
    int getCapacity() const;
};