#include "GameState.h"
#include "Renderer.h"
#include "Tile.h"
#include "Storage.h"
#include "Player.h"
#include "RenderObject.h"
#include "Interface.h"
#include "Chest.h"
#include <chrono>
#include "PhysicsBox.h"
#include "Item.h"
#include "StorageInterface.h"
#include "StorageSlot.h"
#include "ItemStack.h"
#include "RenderGroup.h"
#include "HitboxGroup.h"
#include "TickObject.h"

//g++ -std=c++17 main.cpp StorageInterface.cpp Item.cpp Renderer.cpp TileType.cpp Storage.cpp RenderObject.cpp Tile.cpp Interface.cpp GameState.cpp Player.cpp Chest.cpp MapObject.cpp PhysicsBox.cpp StorageSlot.cpp ItemStack.cpp -o game `sdl2-config --cflags --libs` -lSDL2_image


GameState::GameState(SDL_Renderer* sdlRenderer, int windowWidth, int windowHeight){

    //object groups
    this->Groups = std::vector<RenderGroup*>();
    this->Groups.push_back(this->renderGroup);
    this->Groups.push_back(this->singleFrameGroup);
    this->renderGroup = new RenderGroup();
    this->tickObjects = std::vector<TickObject*>();

    //physic objects groups
    std::vector<PhysicsBox*> moveObjects = std::vector<PhysicsBox*>();
    std::vector<PhysicsBox*> hitboxObjects = std::vector<PhysicsBox*>();
    std::vector<PhysicsBox*> attackObjects = std::vector<PhysicsBox*>();
    std::vector<PhysicsBox*> enemyMoveObjects = std::vector<PhysicsBox*>();
    std::vector<PhysicsBox*> enemyHitboxObjects = std::vector<PhysicsBox*>();
    std::vector<PhysicsBox*> enemyAttackObjects = std::vector<PhysicsBox*>();


    this->sdlRenderer = sdlRenderer;
    this->renderer = new Renderer(sdlRenderer, windowWidth, windowHeight);
    this->renderer->loadTextures("textures");
    
    
    this->singleFrameGroup = new RenderGroup();
    
    this->hitboxGroup = new HitboxGroup();
    this->inInterface = false;
    this->gameRunning = true;
    this->inStorageInterface = false;

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    this->cursorItem = nullptr;

    TickObject::init(this);
    
}


std::vector<int> getMouse(){
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    return {x, y};
}


void GameState::tempTesting(){

    SDL_SetRenderDrawColor(this->sdlRenderer, 20, 25, 40, 255);
    TileType* tt = new TileType(true, "dirt");
    std::vector<RenderObject*> finalRenderObjects = std::vector<RenderObject*>();
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            RenderObject* o = new Tile(i, j, tt);
            registerRenderObjectContinuesly(o);
        }
    }

    Item bottle("Newt", "newt");
    Item newt("Bottle", "bottle");

    Chest* c = new Chest(3, 3, 1, 1, "chest", new Storage(6), this);
    registerRenderObjectContinuesly(c);
    c->getStorage()->addItemToOpenSlots(&bottle, 99);
    c->getStorage()->addItemToOpenSlots(&newt, 99);

    if(c->getStorage()->getItemAtSlot(0) != nullptr){
        //std::cout << c->getStorage()->getItemAtSlot(0)->getTexture() << " wow\n";
    }

    SDL_Event event;
    bool running = true;
    int speed = 5;

    Storage* inv = new Storage(12);
    this->p = new Player(0, 0, 80, 80, "", inv, this);
    registerRenderObjectContinuesly(p);
    moveObjects.push_back(c);
    moveObjects.push_back(p);
    std::vector<int> lastMouse = {0, 0};
    
}


int GameState::mainLoop(){

    //setup
    this->tempTesting();

    //real
    SDL_Event event;
    bool run = true;


    while(run){

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                run = false;
                break;
            }

            doPlayerMovement(p, event);
            if(event.key.keysym.sym == SDLK_r){
                this->renderer->loadTextures("textures");
            }

        }

        if(!run){
            break;
        }

        std::vector<int> mouse = getMouse();
        doCursor(mouse[0], mouse[1]);
        this->renderer->renderAll(this->Groups, true);
        this->singleFrameGroup->empty();
        
    }
    
    return 0;
}


void GameState::doPlayerMovement(Player* p, SDL_Event &event){

    static const int speed = 5;

    if(event.key.keysym.sym == SDLK_w){
        this->p->setMovement(0, 0 - speed);
    }
    else if(event.key.keysym.sym == SDLK_s){
        this->p->setMovement(0, speed);
    }
    else if(event.key.keysym.sym == SDLK_a){
        this->p->setMovement(0 - speed, 0);
    }
    else if(event.key.keysym.sym == SDLK_d){
        this->p->setMovement(speed, 0);
    }

    //reset screen view based on player
    std::vector<int> vec = p->getCenter();
    this->renderer->setScreenX(vec[0] - 300);
    this->renderer->setScreenY(vec[1] - 300);

}


void GameState::registerRenderObjectContinuesly(RenderObject* r){
    this->renderGroup->addObjectToBack(r);
}

void GameState::registerRenderObjectOneFrame(RenderObject* r){
    this->singleFrameGroup->addObjectToBack(r);
}


void GameState::doCursor(int mouseX, int mouseY){

    static RenderObject* cursorRender = new RenderObject(0, 0, 50, 50, "cursor", true);
    static int lastMouseX = mouseX;
    static int lastMouseY = mouseY;
    static int lingerCounter = 0;
    

    if(mouseX < lastMouseX - 40){
        cursorRender->setTexture("lcursor");
        lingerCounter = 30;
    }
    else if(mouseX > lastMouseX + 40){
        cursorRender->setTexture("rcursor");
        lingerCounter = 30;
    }
    else if(lingerCounter < 1){
        cursorRender->setTexture("cursor");
        lingerCounter = 0;
    }
    lingerCounter--;

    cursorRender->setX(mouseX);
    cursorRender->setY(mouseY);
    lastMouseX = mouseX;
    lastMouseY = mouseY;

    this->registerRenderObjectOneFrame(cursorRender);

}


void GameState::doStorageInterface(std::vector<StorageInterface*> interfaces){
    //std::cout << "doStorageInterface(std::vector<StorageInterface*> interfaces)\n";

    static bool lastClickState = false;
    if(this->cursorItem == nullptr){
        //std::cout << "nullptr\n";
    }
    else{
        //std::cout << cursorItem->getItem()->getName() << "\n";
    }

    std::vector<StorageSlot*> allSlots = std::vector<StorageSlot*>();
    std::vector<StorageSlot*> temp;
    for(int i = 0; i < interfaces.size(); i++){
        temp = interfaces.at(i)->getSlots();
        allSlots.insert(allSlots.end(), temp.begin(), temp.end());
    }

        
        for(int i = 0; i < allSlots.size(); i++){

            StorageSlot* currentSlot = allSlots.at(i);
            Storage* currentStorage = currentSlot->getStorage();
            int currentSlotNum = currentSlot->getSlotNum();
            std::vector<int> mouse = getMouse();

            if(this->leftClick && !lastClickState && currentSlot->checkClick(mouse[0], mouse[1])){

                //do storage interact
                if(this->cursorItem == nullptr){
                    this->cursorItem = currentStorage->takeAllFromStackAtSlot(currentSlotNum);
                }
                else if(currentStorage->getItemStackAtSlot(currentSlotNum) == nullptr || cursorItem->getItem()->equals(currentStorage->getItemAtSlot(currentSlotNum))){
                    currentStorage->addItemstackToNumSlot(this->cursorItem, currentSlotNum);
                }
            }
        }

        lastClickState = this->leftClick;

}


void GameState::doMovement(){

    std::vector<int> move = {};
    for(int i = 0; i < this->moveObjects.size(); i++){
        PhysicsBox* current = this->moveObjects.at(i);
        move = current->getMovement();
        if(move[0] != 0 || move[1] != 0){
            for(int j = 0; j < this->moveObjects.size(); j++){
                if(i != j && !current->overLap(this->moveObjects.at(j), move[0], move[1])){
                    current->xMove(move[0]);
                    current->yMove(move[1]);
                }
            }
        }
    }

}


void GameState::registerHitboxObjectContinuesly(PhysicsBox* p){
    this->hitboxGroup->addObjectToFront(p);
}


void GameState::doTicks(){

    for(int i = 0; i < this->tickObjects.size(); i++){
        this->tickObjects.at(i)->doTick();
    }
}
