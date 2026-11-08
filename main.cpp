#include <SDL2/SDL.h> 
#include <iostream>
#include <SDL2/SDL_image.h>
#include "RenderObject.h"
#include <vector>
#include "Renderer.h"
#include "Storage.h"
#include "StorageInterface.h"
#include <cmath>
#include "Tile.h"
#include "GameState.h"

const int WINDOW_WIDTH  = 800;     // Window width
const int WINDOW_HEIGHT = 450;     // Window height


int speed = 5;

int main(int argc, char* argv[]) {

    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    // 2. Create window
    SDL_Window* window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    //error creating window
    if (!window) {
        std::cerr << "CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // 3. Initialize SDL2_image (request PNG support)
    int imgFlags = IMG_INIT_PNG;                                       
    if (!(IMG_Init(imgFlags) & imgFlags)) {                                
        std::cerr << "IMG_Init failed: " << IMG_GetError() << "\n";    
        SDL_Quit();
        return 1;
    }

    // 4. Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    //renderer error
    if (!renderer) {
        std::cerr << "CreateRenderer failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    //temp
    Storage* s = new Storage(12);
    StorageInterface* si = new StorageInterface(350, 10, 580, 200, 170, 0, s, "inventory");

    GameState* g = new GameState(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    g->mainLoop();

    // 4. Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
