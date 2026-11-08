#include "Renderer.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
#include <random>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include "RenderGroup.h"


//temp
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    if (radius < 0) return;                          // Guard against bad input

    for (int dy = -radius; dy <= radius; ++dy) {     // Walk every row of the circle
        int dx = static_cast<int>(std::sqrt(                         // Half-width at this row:
            static_cast<double>(radius * radius - dy * dy)));        //   sqrt(r^2 - dy^2)
        SDL_RenderDrawLine(renderer,                                 // Draw a horizontal span
            cx - dx, cy + dy,                                        //   from (cx-dx, cy+dy)
            cx + dx, cy + dy);                                       //   to   (cx+dx, cy+dy)
    }
}

void drawCircleOutline(SDL_Renderer* renderer, int cx, int cy, int radius) {
    if (radius < 0) return;                          // Guard against bad input

    int x = radius;                                  // Start at the rightmost point
    int y = 0;                                       // and at the horizontal axis
    int err = 1 - radius;                            // Initial decision variable

    while (x >= y) {                                 // Loop through one octant
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);   // Octant 1
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);   // Octant 2
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);   // Octant 3
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);   // Octant 4
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);   // Octant 5
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);   // Octant 6
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);   // Octant 7
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);   // Octant 8

        ++y;                                         // Always step down
        if (err < 0) {                               // If we're still inside the circle
            err += 2 * y + 1;                        //   adjust only y
        } else {                                     // Otherwise we've crossed the boundary
            --x;                                     //   step inward on x too
            err += 2 * (y - x) + 1;                  //   and update the decision variable
        }
    }
}


Renderer::Renderer(SDL_Renderer* rendererSDL, int windowWidth, int windowHeight){

    this->rendererSDL = rendererSDL;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    SDL_ShowCursor(SDL_DISABLE);

}


std::string getRandomTextureFromList(std::vector<std::string> possibleTextures){
    if(possibleTextures.empty()){
        return "";
    }
    else if(possibleTextures.size() == 1){
        return possibleTextures[0];
    }

    static thread_local std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<std::size_t> dist(0, possibleTextures.size() - 1);
    return possibleTextures[dist(gen)];
}

void Renderer::renderAll(std::vector<RenderGroup*> rends, bool frameTime){

    auto start = std::chrono::steady_clock::now();

    SDL_RenderClear(this->rendererSDL);
    for(int i = 0; i < rends.size(); i++){
        renderAll(rends.at(i), true, 0, 0);
    }
    SDL_RenderPresent(this->rendererSDL); 

    auto end = std::chrono::steady_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if(frameTime){
        std::cout << "Render time: " << duration_ms.count() << " ms\n";
    }
}


void Renderer::renderAll(RenderGroup* g){

    SDL_RenderClear(this->rendererSDL);
    renderAll(g, true, 0, 0);
    SDL_RenderPresent(this->rendererSDL); 

}


void Renderer::renderAll(RenderGroup* g, bool clear, int xOffset, int yOffset){

    RenderObjectContainer* prev = nullptr;
    RenderObjectContainer* current = g->getFirstObject();

    while(current != nullptr){

        if(current->getObjectPointer() == nullptr || current->getObject() == nullptr){
            current = current->getNextObject();
            g->remove(current, prev);
            continue;
        }

        RenderObject* o = current->getObject();
        SDL_Rect rect;

        //position object
        if(!o->isPosAbsolute()){
            rect = {(o->getXPos() + xOffset) - this->topLeftX, (o->getYPos() + yOffset) - this->topLeftY, o->getWidth(), o->getHeight()};
        }
        else{ 
            rect = {(o->getXPos() + xOffset), (o->getYPos() + yOffset), o->getWidth(), o->getHeight()};
        }

        //render object
        if(o->isVisible()){

            //get texture if render object is pulling from a texture group
            if(o->usingGroup()){
                o->setTexture(getRandomTextureFromList(this->textureGroup[o->getTextureName()]));
                o->setUsingGroup(false);
            }
            //render
            if(this->textures[o->getTextureName()] != nullptr){
                SDL_RenderCopy(this->rendererSDL, this->textures[o->getTextureName()], nullptr, &rect); 
            }
            //display error color rect
            else{
                std::vector<int> errorColor = o->getErrorColor();
                SDL_SetRenderDrawColor(this->rendererSDL, errorColor[0], errorColor[1], errorColor[2], errorColor[3]); 
                SDL_RenderFillRect(this->rendererSDL, &rect);
                SDL_RenderDrawRect(this->rendererSDL, &rect);
            }

            if(o->hasSubObjects()){
                renderAll(o->getSubObjects(), false, o->getXPos() + xOffset, o->getYPos() + yOffset);
            }
        }

        prev = current;
        current = current->getNextObject();

    }

}


/*
void Renderer::renderAll(std::vector<RenderObject*> objects){
    renderAll(objects, true, 0, 0);
}
*/


void Renderer::renderAll(std::vector<RenderObject*> objects, bool clear, int xOffset, int yOffset){

    auto start = std::chrono::steady_clock::now();
    SDL_ShowCursor(SDL_DISABLE);

    if(clear){
        SDL_RenderClear(this->rendererSDL);
    }

    for(int i = 0; i < objects.size(); i++){

        RenderObject* o = objects.at(i);
        SDL_Rect rect;
        if(o == nullptr){
            continue;
        }

        if(!o->isPosAbsolute()){
            rect = {(o->getXPos() + xOffset) - this->topLeftX, (o->getYPos() + yOffset) - this->topLeftY, o->getWidth(), o->getHeight()};
        }
        else{ 
            rect = {(o->getXPos() + xOffset), (o->getYPos() + yOffset), o->getWidth(), o->getHeight()};
        }

        if(o->isVisible()){
            if(o->usingGroup()){
                o->setTexture(getRandomTextureFromList(this->textureGroup[o->getTextureName()]));
                o->setUsingGroup(false);
            }
            if(this->textures[o->getTextureName()] != nullptr){
                SDL_RenderCopy(this->rendererSDL, this->textures[o->getTextureName()], nullptr, &rect); 
            }
            else{
                std::vector<int> errorColor = o->getErrorColor();
                SDL_SetRenderDrawColor(this->rendererSDL, errorColor[0], errorColor[1], errorColor[2], errorColor[3]); 
                SDL_RenderFillRect(this->rendererSDL, &rect);
                SDL_RenderDrawRect(this->rendererSDL, &rect);
            }
        }

        if(o->hasSubObjects()){
            renderAll(o->getSubObjects(), false, o->getXPos() + xOffset, o->getYPos() + yOffset);
        }

    }

    if(clear){
        SDL_RenderPresent(this->rendererSDL); 

        auto end = std::chrono::steady_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        //std::cout << "Render time: " << duration_ms.count() << " ms\n";
    }

}


std::string getBasename(const std::string& filename) {

    size_t lastSlash = filename.find_last_of("/\\");
    size_t nameStart = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;

    size_t lastDot = filename.find_last_of('.');

    if (lastDot == std::string::npos ||
        lastDot < nameStart ||
        lastDot == nameStart) {
        return filename.substr(nameStart);
    }

    return filename.substr(nameStart, lastDot - nameStart);
}


std::vector<std::string> getFileNames(std::string folderPath, bool recursive = false){

    std::vector<std::string> names;

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Invalid directory: " << folderPath << '\n';
        return names;
    }

    if (recursive) {
        for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
            if (entry.is_regular_file())
                names.push_back(entry.path().filename().string());
        }
    } else {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            names.push_back(entry.path().filename().string());
        }
    }

    return names;
}


void Renderer::loadTextureGroup(std::string folderPath, std::string groupName){

    std::vector<std::string> textureFiles = getFileNames(folderPath, false);
    std::vector<std::string> vec = std::vector<std::string>();

    for(int i = 0; i < textureFiles.size(); i++){


        //std::cout << textureFiles.at(i) << "\n";
        SDL_Texture* texture = IMG_LoadTexture(this->rendererSDL, (folderPath + "/" + textureFiles.at(i)).c_str());
        std::string textureName = getBasename(textureFiles.at(i));
        if(!texture){
            continue;
        }

        this->textures[textureFiles.at(i)] = texture;
        vec.push_back(textureFiles.at(i));

    }
    //std::cout << "loaded texture group " << groupName << ": ";
    for(int i = 0; i < vec.size() - 1; i++){
        //std::cout << vec.at(i) << ", ";
    }
    //std::cout << vec.at(vec.size() - 1) << "\n";
    this->textureGroup[groupName] = vec;
}


void Renderer::loadTextures(std::string texturesFolder){

    std::vector<std::string> textureFiles = getFileNames(texturesFolder, false);

    for(int i = 0; i < textureFiles.size(); i++){

        fs::path p = texturesFolder + "/" + textureFiles.at(i);
        //std::cout << "checking: " << textureFiles.at(i) << "\n";
    
        if (!fs::exists(p) || textureFiles.at(i) == "Archive") {
            continue;
        } 
        else if (fs::is_directory(p)) {
            loadTextureGroup(texturesFolder + "/" + textureFiles.at(i), textureFiles.at(i));
            continue;
        }

        std::cout << "loaded texture " << textureFiles.at(i) << "\n";
        SDL_Texture* texture = IMG_LoadTexture(this->rendererSDL, (texturesFolder + "/" + textureFiles.at(i)).c_str());
        std::string textureName = getBasename(textureFiles.at(i));
        if(!texture){
            this->textures[textureName] = nullptr;
            //std::cout << "failed to load texture " << textureName << "\n";
            continue;
        }
        this->textures[textureName] = texture;
    }

}


void Renderer::moveScreenX(int x){
    this->topLeftX += x;
}

void Renderer::moveScreenY(int y){
    this->topLeftY += y;
}

void Renderer::setScreenX(int x){
    this->topLeftX = x;
}

void Renderer::setScreenY(int y){
    this->topLeftY = y;
}


