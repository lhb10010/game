#include "RenderObject.h"
#include <string>
#include <random>
#include "PhysicsBox.h"
#include <iostream>


static int lastId = 0;


int randomByte() {
    static std::random_device rd;      // Seed (hardware entropy)
    static std::mt19937 gen(rd());     // Mersenne Twister engine
    static std::uniform_int_distribution<int> dist(0, 255);
    return dist(gen);
}


std::vector<int> RenderObject::getErrorColor(){
    return this->errorColor;
}


RenderObject::RenderObject(int x, int y, int w, int h, std::string texture){

    this->xPos = x;
    this->yPos = y;
    this->width = w;
    this->height = h;
    this->texture = texture;
    this->absolutePos = false;
    this->visible = true;
    this->isGroup = false;;
    this->id = lastId;
    lastId++;

    this->xAbsolutePos = x;
    this->yAbsolutePos = y;

    this->subObjects = std::vector<RenderObject*>();
    this->errorColor = {randomByte(), randomByte(), randomByte(), randomByte()};

    this->doubleP = nullptr;

}

/*
RenderObject::RenderObject(int x, int y, int w, int h, std::string texture, bool isGroup){

    this->xPos = x;
    this->yPos = y;
    this->width = w;
    this->height = h;
    this->texture = texture;
    this->absolutePos = false;
    this->visible = true;
    this->isGroup = isGroup;

    this->subObjects = std::vector<RenderObject*>();
    this->errorColor = {randomByte(), randomByte(), randomByte(), randomByte()};

}
*/


RenderObject::RenderObject(int x, int y, int w, int h, std::string texture, bool isAbsolute){

    this->xPos = x;
    this->yPos = y;
    this->width = w;
    this->height = h;
    this->texture = texture;
    this->absolutePos = isAbsolute;
    this->visible = true;
    this->isGroup = false;
    this->id = lastId;
    lastId++;

    this->xAbsolutePos = x;
    this->yAbsolutePos = y;

    this->subObjects = std::vector<RenderObject*>();
    this->errorColor = {randomByte(), randomByte(), randomByte(), randomByte()};

    this->doubleP = nullptr;

}


RenderObject::RenderObject(int x, int y, int w, int h, std::string texture, bool isAbsolute, bool isGroup){

    this->xPos = x;
    this->yPos = y;
    this->width = w;
    this->height = h;
    this->texture = texture;
    this->absolutePos = isAbsolute;
    this->visible = true;
    this->isGroup = isGroup;
    this->id = lastId;
    lastId++;
    
    this->xAbsolutePos = x;
    this->yAbsolutePos = y;

    this->subObjects = std::vector<RenderObject*>();
    this->errorColor = {randomByte(), randomByte(), randomByte(), randomByte()};

    this->doubleP = nullptr;

}

RenderObject::~RenderObject(){

    for(int i = 0; i < this->subObjects.size(); i++){
        delete this->subObjects.at(i);
    }

    if(this->doubleP != nullptr){
        *doubleP = nullptr;
    }

}


void RenderObject::setDoublePointer(RenderObject** dp){

    this->doubleP = dp;

}


int RenderObject::getXPos(){
    return this->xPos;
}


int RenderObject::getYPos(){
    return this->yPos;
}


int RenderObject::getWidth(){
    return this->width;
}


int RenderObject::getHeight(){
    return this->height;
}


std::string RenderObject::getTextureName(){
    return this->texture;
}

bool RenderObject::hasSubObjects(){
    if(this->subObjects.empty()){
        return false;
    }
    return true;
}

std::vector<RenderObject*> RenderObject::getSubObjects(){

    //std::cout << "wow1\n";
    //std::cout << this->subObjects.size() << "\n";

    return this->subObjects;

}

void RenderObject::setSubObjects(std::vector<RenderObject*> vec){

    for(int i = 0; i < this->subObjects.size(); i++){
        if(this->subObjects.at(i) == nullptr){
            continue;
        }
        this->subObjects.at(i)->xAbsolutePos = this->subObjects.at(i)->xPos;
        this->subObjects.at(i)->yAbsolutePos = this->subObjects.at(i)->yPos;
    }

   
    for(int i = 0; i < vec.size(); i++){
        if(vec.at(i) == nullptr){
            continue;
        }
        vec.at(i)->xAbsolutePos += this->xAbsolutePos;
        vec.at(i)->yAbsolutePos += this->yAbsolutePos;
    }

    this->subObjects = vec;
    
}

bool RenderObject::isPosAbsolute(){
    return this->absolutePos;
}


bool RenderObject::isVisible(){
    return this->visible;
}


void RenderObject::setVisible(bool visible){
    this->visible = visible;
}

bool RenderObject::usingGroup(){
    return this->isGroup;
}

void RenderObject::setUsingGroup(bool isGroup){
    this->isGroup = isGroup;
}

void RenderObject::setTexture(std::string texture){
    this->texture = texture;
}


std::vector<int> RenderObject::getCenter(){

    int x = (this->xPos + this->xPos + width) / 2;
    int y = (this->yPos + this->yPos + height) / 2;

    return {xPos, yPos};

}

void RenderObject::moveX(int x){
    this->xPos += x;
    if(PhysicsBox* d = dynamic_cast<PhysicsBox*>(this)){
        d->setX(this->xPos);
    }
}

void RenderObject::moveY(int y){
    this->yPos += y;
    if(PhysicsBox* d = dynamic_cast<PhysicsBox*>(this)){
        d->setX(this->yPos);
    }
}

void RenderObject::setX(int x){
    this->xPos = x;
}

void RenderObject::setY(int y){
    this->yPos = y;
}


int RenderObject::getAbsoluteX(){
    return this->xAbsolutePos;
}

int RenderObject::getAbsoluteY(){
    return this->yAbsolutePos;
}