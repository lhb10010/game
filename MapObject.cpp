#include "MapObject.h"
#include <string>
#include "Tile.h"


MapObject::MapObject(int tileX, int tileY, int tileWidth, int tileHeight, std::string texture) : RenderObject(tileX * Tile::TILE_WIDTH, tileY * Tile::TILE_WIDTH, tileWidth* Tile::TILE_WIDTH, tileHeight * Tile::TILE_WIDTH, texture){



}


void MapObject::interact(Player* p){


}


void MapObject::attack(){


}