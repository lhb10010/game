#include "Tile.h"
#include <random>


Tile::Tile(int stagePosX, int stagePosY, Stage* s, TileType* t) 
: RenderObject(stagePosX * TILE_WIDTH, stagePosY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, t->getTexturePool(), false, true){
    this->stage = s;
    this->type = t;
    this->stagePosX = stagePosX;
    this->stagePosY = stagePosY;
}


Tile::Tile(int stagePosX, int stagePosY, TileType* t) 
: RenderObject(stagePosX * TILE_WIDTH, stagePosY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, t->getTexturePool(), false, true){
    this->type = t;
    this->stagePosX = stagePosX;
    this->stagePosY = stagePosY;
}

Tile::Tile(int stagePosX, int stagePosY, std::string texture) : RenderObject(stagePosX * TILE_WIDTH, stagePosY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, texture){
    this->stagePosX = stagePosX;
    this->stagePosY = stagePosY;
    this->texture = texture;
}