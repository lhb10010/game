#ifndef MAPOBJECT_H
#define MAPOBJECT_H

class Player;
#include "RenderObject.h"
#include <string>

class MapObject : public RenderObject{

    public:
        MapObject(int tileX, int tileY, int tileWidth, int tileHeight, std::string texture);
        virtual void interact(Player* p);
        virtual void attack();

    private:
        int tilePosX;
        int tilePosY;

};


#endif