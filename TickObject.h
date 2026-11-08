#include "GameState.h"
#ifndef TICKOBJECT_H
#define TICKOBJECT_H

class TickObject{

    public:
        static void init(GameState* gameState);
        TickObject();
        void registerToDoTicks();
        virtual void doTick();

    private:
        
        static GameState* gameStateObj;


};

#endif