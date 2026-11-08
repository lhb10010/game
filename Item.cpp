#include "Item.h"
#include "RenderObject.h"

Item::Item(std::string name, std::string texture){

    this->name = name;
    this->texture = texture;
}


std::string Item::getTexture(){
    return this->texture;
}

std::string Item::getName(){
    return this->name;
}


RenderObject* Item::makeRenderObject(int x, int y, int width, int height, bool absolutePos){
    return new RenderObject(x, y, width, height, this->texture, absolutePos);
}


bool Item::equals(Item* i){

    if(i == nullptr){
        return false;
    }

    if(i->name == this->name){
        return true;
    }
    return false;
}