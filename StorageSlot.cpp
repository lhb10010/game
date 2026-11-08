#include "StorageSlot.h"
#include "Item.h"
#include "Storage.h"
#include <iostream>
#include "StorageInterface.h"

StorageSlot::StorageSlot(int x, int y, int width, int height, std::string texture, int slotNum, Storage* s) : RenderObject(x, y, width, height, texture, true){
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    this->slotNum = slotNum;
    this->s = s;
}


bool StorageSlot::checkClick(int x, int y){

    std::cout << x << " " << this->xPos << " " << this->xPos + width << " " << y << " " << this->yPos << " " << this->yPos + height << "\n";

    if(x >= this->getAbsoluteX() && x <= this->getAbsoluteX() + width && y >= this->getAbsoluteY() && y <= this->getAbsoluteY() + height){
        return true;
    }
    return false;
}


Storage* StorageSlot::getStorage(){
    return this->s;
}


int StorageSlot::getSlotNum(){
    return this->slotNum;
}


void StorageSlot::loadItemTexture(){

    Item* i = this->s->getItemAtSlot(this->slotNum);
    std::vector<RenderObject*> vec = std::vector<RenderObject*>();

    if(i != nullptr){
  
        vec.push_back(new RenderObject(0, 0, this->width, this->height, i->getTexture(), true));

    }

    this->setSubObjects(vec);

}