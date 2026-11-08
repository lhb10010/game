#include "Storage.h"
#include "Item.h"
#include <iostream>
#include "ItemStack.h"

Storage::Storage(int slots){

    this->itemStacks = std::vector<ItemStack*>(slots, nullptr);

}

int Storage::addItemToOpenSlots(Item* i, int count){
    ItemStack* s = new ItemStack(i, count);
    return addItemToOpenSlots(s);
}

int Storage::addItemToOpenSlots(ItemStack* &is){
    //std::cout << "addItemToOpenSlots(ItemStack* &is)\n";

    int canAdd;
    int firstNullSlot = -1;
    for(int i = 0; i < this->itemStacks.size(); i++){

        //slot has the existing item
        if(this->itemStacks[i] != nullptr && this->itemStacks[i]->getItem()->equals(is->getItem())){
            canAdd = MAX_STACK - this->itemStacks[i]->getItemCount();
            if(canAdd > is->getItemCount()){
                this->itemStacks[i]->incCount(is->getItemCount());
                ItemStack* temp = is;
                delete temp;
                is = nullptr;
                return 0;
            }
            else{
                this->itemStacks[i]->incCount(canAdd);
                is->decCount(canAdd);
            }
        }
        else if(firstNullSlot == -1 && this->itemStacks[i] == nullptr){
            firstNullSlot = i;
        }
    }

    if(firstNullSlot != -1){
        this->itemStacks[firstNullSlot] = new ItemStack(is->getItem(), is->getItemCount());
        ItemStack* temp = is;
        delete temp;
        is = nullptr;
        return 0;
    }

    return is->getItemCount();

}


int Storage::getSlots(){
    return this->itemStacks.size();
}


Item* Storage::getItemAtSlot(int slotNum){
    //std::cout << "Storage::getItemAtSlot(int slotNum)\n";

    if(slotNum >= this->itemStacks.size()){
        return nullptr;
    }

    if(this->itemStacks[slotNum] == nullptr){
        return nullptr;
    }

    return this->itemStacks[slotNum]->getItem();

}


ItemStack* Storage::getItemStackAtSlot(int slotNum){
    //std::cout << "getItemStackAtSlot(int slotNum)\n";

    if(slotNum >= this->itemStacks.size()){
        return nullptr;
    }

    return this->itemStacks[slotNum];

}


ItemStack* Storage::takeAllFromStackAtSlot(int slotNum){
    //std::cout << "takeAllFromStackAtSlot(int slotNum)\n";

    if(slotNum >= this->itemStacks.size() || this->itemStacks[slotNum] == nullptr){
        return nullptr;
    }

    return takeNumItemsFromStackAtSlot(slotNum, this->itemStacks[slotNum]->getItemCount());

}


ItemStack* Storage::takeNumItemsFromStackAtSlot(int slotNum, int itemCount){
    //std::cout << "takeNumItemsFromStackAtSlot(int slotNum, int itemCount)\n";

    if(slotNum >= this->itemStacks.size()){
        return nullptr;
    }

    if(itemCount >= this->itemStacks[slotNum]->getItemCount()){
        ItemStack* i = this->itemStacks[slotNum];
        this->itemStacks[slotNum] = nullptr;
        return i;
    }

    this->itemStacks[slotNum]->decCount(itemCount);
    return new ItemStack(this->itemStacks[slotNum]->getItem(), itemCount);

}


void Storage::addItemstackToNumSlot(ItemStack* &i, int slotNum){
    //std::cout << "addItemstackToNumSlot(ItemStack* &i, int slotNum)\n";

    if(slotNum >= this->itemStacks.size()){
        return;
    }

    if(this->itemStacks[slotNum] == nullptr){
        this->itemStacks[slotNum] = i;
        i = nullptr;
        return;
    }
    else if(this->itemStacks[slotNum]->getItem()->equals(i->getItem()) && i->getItemCount() > MAX_STACK - this->itemStacks[slotNum]->getItemCount()){
        i->decCount(MAX_STACK - this->itemStacks[slotNum]->getItemCount());
        this->itemStacks[slotNum]->setItemCount(MAX_STACK);
    }

}