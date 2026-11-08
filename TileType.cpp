#include "TileType.h"

TileType::TileType(bool isWalkable, std::string texturePool){
    this->texturePool = texturePool;
    this->isWalkable = isWalkable;
}

TileType::TileType(){
    
}


std::string TileType::getTexturePool(){

    return this->texturePool;

}