#include "StorageInterface.h"
#include <cmath>
#include "Storage.h"
#include "Item.h"
#include <iostream>
#include "StorageSlot.h"

StorageInterface::StorageInterface(int screenX, int ScreenY, int width, int height, int xSlotOffset, int ySlotOffset, Storage* s, std::string texture) : Interface(screenX, ScreenY, width, height, texture){

    width = width - xSlotOffset;
    height = height - ySlotOffset;

    this->targetStore = s;

    float fWidth = width;
    float fHeight = height;
    std::cout << 0 + xSlotOffset << " " << 0 + ySlotOffset << " " << width << " " << height << "\n";
    slotContainerSubObject = new RenderObject(0 + xSlotOffset, 0 + ySlotOffset, width, height, "", true);
    slotContainerSubObject->setVisible(false);
    this->numSlotsWidth;
    this->numSlotsHeight;
    bool isLeftRight = true;
    int ratio;
    if(width > height){
        ratio = std::round(fWidth / fHeight);
        int i = 1;
        //std::cout << ratio << "\n";
        while(true){
            this->numSlotsWidth = ratio * i;
            this->numSlotsHeight = i;
            if(numSlotsWidth * numSlotsHeight >= s->getSlots()){
                break;
            }
            i++;
        } 
    }
    else{
        this->numSlotsWidth = std::round(height / width);
        this->numSlotsHeight = s->getSlots() / numSlotsWidth;
        isLeftRight = false;
    }

    int widthUnit = (numSlotsWidth * 3) + ((numSlotsWidth + 1) * 2);
    this->widthUnitSize = width / widthUnit;

    int heightUnit = (numSlotsHeight * 3) + ((numSlotsHeight + 1) * 2);
    this->heightUnitSize = height / heightUnit;


    this->slots = std::vector<StorageSlot*>();

    int slotNum = 0;
    int posX = widthUnitSize * 2;
    int posY = heightUnitSize * 2;
    Item* item;

    for(int i = 0; i < numSlotsHeight; i++){
        for(int j = 0; j < numSlotsWidth; j++){

            //std::cout << slotNum << ": " << posX << " " << posY << " " << widthUnitSize * 3 << " " << heightUnitSize * 3 << numSlotsWidth << " " << 
            //numSlotsWidth << " " << numSlotsHeight << "\n";

            //slot image
            this->slots.push_back(new StorageSlot(posX + xSlotOffset, posY + ySlotOffset, widthUnitSize * 3, heightUnitSize * 3, "slot", slotNum, this->targetStore));

            slotNum++;
            posX += widthUnitSize * 5;
            if(slotNum >= s->getSlots()){
                break;
            }
        }
        if(slotNum >= s->getSlots()){
            break;
        }
        posY += heightUnitSize * 5;
        posX = widthUnitSize * 2;
    }

    std::vector<RenderObject*> baseVec(this->slots.begin(), this->slots.end());
    this->setSubObjects(baseVec);

}



void StorageInterface::getItemSubRenders(){

    int slotNum = 0;
    int posX = widthUnitSize * 2;
    int posY = heightUnitSize * 2;
    Item* item;

    for(int i = 0; i < numSlotsHeight; i++){
        for(int j = 0; j < numSlotsWidth; j++){

            //item image
            this->slots.at(slotNum)->loadItemTexture();

            slotNum++;
            posX += widthUnitSize * 5;
            if(slotNum >= targetStore->getSlots()){
                break;
            }

        }
        if(slotNum >= targetStore->getSlots()){
            break;
        }
        posY += heightUnitSize * 5;
        posX = widthUnitSize * 2;
    }

}

std::vector<StorageSlot*> StorageInterface::getSlots(){

    return this->slots;

}