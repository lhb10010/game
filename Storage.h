#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
class Item;
class ItemStack;

class Storage{

    static const int MAX_STACK = 100;

    public:
        Storage(int slots);
        int addItemToOpenSlots(ItemStack* &is);
        int getSlots();
        Item* getItemAtSlot(int slotNum);
        ItemStack* getItemStackAtSlot(int slotNum);
        ItemStack* takeNumItemsFromStackAtSlot(int slotNum, int itemCount);
        void addItemstackToNumSlot(ItemStack* &i, int slotNum);
        ItemStack* takeAllFromStackAtSlot(int slotNum);
        int addItemToOpenSlots(Item* i, int count);

    private:
        std::vector<ItemStack*> itemStacks;

};

#endif