#ifndef PLAYER_H
#define PLAYER_H

#include "RenderObject.h"
#include "PhysicsBox.h"
class Storage;
class GameState;

class Player : public RenderObject, public PhysicsBox{

    public:
        Player(int x, int y, int width, int height, std::string texture, Storage* inv, GameState* g);
        void openInventory();
        void setMovement(int x, int y);

    private:
        Storage* inventory;
        GameState* game;
        int nextMoveX;
        int nextMoveY;
        
};

#endif