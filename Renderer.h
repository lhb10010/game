#include <vector>
#include "RenderObject.h"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#ifndef RENDERER_H
#define RENDERER_H

class RenderGroup;


class Renderer{

    public:
        Renderer(SDL_Renderer* rendererSDL, int windowWidth, int windowHeight);
        //void renderAll(std::vector<RenderObject*> objects);
        void renderAll(RenderGroup* g);
        void renderAll(std::vector<RenderGroup*> rends, bool frameTime);
        void loadTextures(std::string textureFiles);
        void moveScreenX(int x);
        void moveScreenY(int y);
        void setScreenX(int x);
        void setScreenY(int y);

    private:
        int topLeftX;
        int topLeftY;
        SDL_Renderer* rendererSDL;
        std::unordered_map<std::string, SDL_Texture*> textures;
        std::unordered_map<std::string, std::vector<std::string>> textureGroup;
        void renderAll(std::vector<RenderObject*> objects, bool clear, int xOffset, int yOffset);
        void renderAll(RenderGroup* g, bool clear, int xOffset, int yOffset);
        void loadTextureGroup(std::string folderPath, std::string groupName);

        std::unordered_map<int, std::vector<int>> errorColors;

        int windowWidth;
        int windowHeight;
};

#endif