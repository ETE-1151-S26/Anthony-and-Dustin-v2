#pragma once
#include <string>
#include "Item.hpp"

class Inventory
{
private:
    static const int Capacity = 10;
    Item items[Capacity];//fixed size storage for Item objects
    int count;

public:
    Inventory();
    
    bool addItem(const Item& item);//adds item to inventory if there's space, returns true if successful, false if inventory is full
    bool removeItemByName(const std::string& name);//removes first item with matching name, returns true if successful, false if not found
    bool getItemByName(const std::string& name, Item& outItem) const;//searches inventory for item by name, if found copies it to outItem and returns true, otherwise returns false

    void display() const;//prints ineventory contents 

    int getCount() const;
    int getCapacity() const;
};