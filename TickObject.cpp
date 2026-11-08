#include "TickObject.h"

void TickObject::init(GameState* gameState){
    gameStateObj = gameState;
}

TickObject::TickObject(){

}

void TickObject::registerToDoTicks(){
    gameStateObj->registerTickObjectContinuesly(this);
}

void TickObject::doTick(){
    return;
}
