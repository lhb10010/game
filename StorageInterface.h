#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include "RenderObject.h"
#include <iostream>
#include "Interface.h"
class Item;
class Storage;
class StorageSlot;


class StorageInterface : public Interface{

    public:
        //StorageInterface(int screenX, int ScreenY, int width, int height, Storage* s, std::string texture);
        StorageInterface(int screenX, int ScreenY, int width, int height, int xSlotOffset, int ySlotOffset, Storage* s, std::string texture);
        std::vector<StorageSlot*> getSlots();

        std::vector<RenderObject*> getSubObjects() override{
            getItemSubRenders();
            return this->subObjects;
        }

    private:
        Storage* targetStore;
        std::vector<StorageSlot*> slots;
        void getItemSubRenders();
        RenderObject* slotContainerSubObject;

        int numSlotsWidth;
        int numSlotsHeight;
        int widthUnitSize;
        int heightUnitSize;
        

};

#endif