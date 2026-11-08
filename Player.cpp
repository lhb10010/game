#include "Player.h"
#include "StorageInterface.h"
#include "GameState.h"
#include "PhysicsBox.h"


Player::Player(int x, int y, int width, int height, std::string texture, Storage* inv, GameState* g) 
: RenderObject(x, y, width, height, texture, false), PhysicsBox(x, y, width, height){

    this->inventory = inv;
    this->game = g;

}

void Player::setMovement(int x, int y){
    this->nextMoveX = x;
    this->nextMoveY = y;
}

void Player::openInventory(){

    //this->game->openInterface(new StorageInterface(0, 0, 900, 150, 170, 0, this->inventory, "inventory"));

}