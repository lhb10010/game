#include <vector>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include "RenderGroup.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class RenderObject;
class Interface;
class Renderer;
class PhysicsBox;
class StorageInterface;
class ItemStack;
class Player;
class RenderGroup;
class HitboxGroup;
class TickObject;


class GameState{

    public:
        GameState(SDL_Renderer* sdlRenderer, int windowWidth, int windowHeight);
        int mainLoop();
        void openInterface(std::vector<Interface*> interfaces);
        void openInterface(Interface* interfaces);
        void closeInterface();
        void doStorageInterface(std::vector<StorageInterface*> interfaces);
        void registerRenderObjectContinuesly(RenderObject* r);
        void registerRenderObjectOneFrame(RenderObject* r);

        void registerHitboxObjectContinuesly(PhysicsBox* r);
        void registerTickObjectContinuesly(TickObject* t);

    private:

        //private functions
        void doMovement();
        void doCursor(int mouseX, int mouseY);
        void doPlayerMovement(Player* p, SDL_Event &event);
        void tempTesting();
        void doTicks();

        //
        std::vector<RenderGroup*> Groups;
        RenderGroup* renderGroup;
        RenderGroup* singleFrameGroup;
        HitboxGroup* hitboxGroup;


        bool gameRunning;
        bool inInterface;
        bool inStorageInterface;

        Player* p;

        std::vector<PhysicsBox*> moveObjects;
        std::vector<PhysicsBox*> hitboxObjects;
        std::vector<PhysicsBox*> attackObjects;
        std::vector<PhysicsBox*> enemyMoveObjects;
        std::vector<PhysicsBox*> enemyHitboxObjects;
        std::vector<PhysicsBox*> enemyAttackObjects;


        std::vector<TickObject*> tickObjects;

        

        Renderer* renderer;
        SDL_Renderer* sdlRenderer;

        int windowWidth;
        int windowHeight;

        bool leftClick;

        ItemStack* cursorItem;


        int forwardMoveKey = SDLK_w;
        int backwardMoveKey = SDLK_s;
        int leftMoveKey = SDLK_a;
        int rightMoveKey = SDLK_d;

        int reloadTexturesKey = SDLK_r;

};

#endif