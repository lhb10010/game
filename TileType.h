#ifndef TILETYPE_H
#define TILETYPE_H

#include <vector>
#include <string>

class TileType{

    public:
        TileType(bool isWalkable, std::string texturePool);
        TileType();
        std::string getTexturePool();

    private:
        bool isWalkable;
        std::string texturePool;

};

#endif