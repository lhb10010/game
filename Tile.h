
#ifndef TILE_H
#define TILE_H

#include "RenderObject.h"
#include "TileType.h"
class Stage;

class Tile : public RenderObject{

    public:
        Tile(int stagePosX, int stagePosY, Stage* s, TileType* t);
        Tile(int stagePosX, int stagePosY, TileType* t);
        Tile(int stagePosX, int stagePosY, std::string texture);
        static const int TILE_WIDTH = 60;

    private:
        int stagePosX;
        int stagePosY;
        TileType* type;
        Stage* stage;

};

#endif