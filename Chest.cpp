#include "Chest.h"
#include "Player.h"
#include "StorageInterface.h"
#include "GameState.h"
#include "PhysicsBox.h"


Chest::Chest(int tileX, int tileY, int tileWidth, int tileHeight, std::string texture, Storage* s, GameState* g)
 : MapObject(tileX, tileY, tileWidth, tileHeight, texture)
, PhysicsBox(tileX * 60, tileY * 60, tileWidth * 60, tileHeight * 60){

    this->store = s;
    this->gameState = g;
    
}

void Chest::chestInteract(Player* p){

    p->openInventory();
    //this->gameState->openInterface(new StorageInterface(-50, 150, 900, 300, 20, 150, this->store, "chestinventory"));

}


Storage* Chest::getStorage(){
    return this->store;
}