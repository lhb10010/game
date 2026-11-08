#ifndef CHEST_H
#define CHEST_H


#include "MapObject.h"
#include "PhysicsBox.h"
class Storage;
class Player;
class GameState;


class Chest : public MapObject, public PhysicsBox{

    public:
        Chest(int tileX, int tileY, int tileWidth, int tileHeight, std::string texture, Storage* s, GameState* g);
        Storage* getStorage();

    void interact(Player* p) override{
        chestInteract(p);
    }

    private:
        Storage* store;
        void chestInteract(Player* p);
        GameState* gameState;

};


#endif