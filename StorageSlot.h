#ifndef STORAGESLOT_H
#define STORAGESLOT_H

#include "RenderObject.h"
class Storage;

class StorageSlot : public RenderObject{

    public:
        StorageSlot(int x, int y, int width, int height, std::string texture, int slotNum, Storage* s);

        bool checkClick(int x, int y);
        Storage* getStorage();
        int getSlotNum();
        void loadItemTexture();

    private:

        Storage* s;
        int slotNum;
        int xPos;
        int yPos;
        int width;
        int height;



};


#endif