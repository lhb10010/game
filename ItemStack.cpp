#include "ItemStack.h"
#include <iostream>

ItemStack::ItemStack(Item* item, int count){
    this->item = item;
    this->count = count;
}

Item* ItemStack::getItem(){
    //std::cout << "ItemStack::getItem()\n";
    return this->item;
}

int ItemStack::getItemCount(){
    return this->count;
}

void ItemStack::setItemCount(int count){
    this->count = count;
}


void ItemStack::incCount(int n){
    this->count += n;
}


void ItemStack::decCount(int n){
    this->count -= n;
}