#include "RenderGroup.h"
#include <iostream>


RenderObjectContainer::RenderObjectContainer(RenderObject* obj){
    this->object = new RenderObject*[1];
    *object = obj;
    this->nextObject = nullptr;
}

RenderObject** RenderObjectContainer::getObjectPointer(){
    return object;
}

void RenderObjectContainer::setNextObject(RenderObjectContainer* obj){
    this->nextObject = obj;
}

RenderObjectContainer* RenderObjectContainer::getNextObject(){
    return this->nextObject;
}

RenderObject* RenderObjectContainer::getObject(){
    return *object;
}

void RenderObjectContainer::deleteContainedObject(){
    RenderObject* temp = *object;
    delete temp;
    *object = nullptr;
}

RenderObjectContainer::~RenderObjectContainer(){
    RenderObject** pointer = object;
    delete pointer;
}




RenderGroup::RenderGroup(std::vector<RenderObject*> objects){

    if(objects.size() < 1){
        this->lastObject = nullptr;
        this->firstObject = nullptr;
        this->objectCount = 0;
    }

    RenderObjectContainer* first = new RenderObjectContainer(objects.at(0));
    this->firstObject = first;
    this->objectCount = objects.size();

    RenderObjectContainer* last = first;
    RenderObjectContainer* current;

    for(int i = 1; i < objects.size(); i++){
        current = new RenderObjectContainer(objects.at(i));
        last->setNextObject(current);
        last = current;
    }

    this->lastObject = last;

}

RenderGroup::RenderGroup(){
    this->lastObject = nullptr;
    this->firstObject = nullptr;
    this->objectCount = 0;
}

void RenderGroup::addObjectToFront(RenderObject* obj){

    if(obj == nullptr){
        return;
    }

    RenderObjectContainer* r = new RenderObjectContainer(obj);
    
    if(this->firstObject == nullptr){
        this->lastObject = r;
    }
        
    r->setNextObject(this->firstObject);
    this->firstObject = r;
    
    this->objectCount++;

}

void RenderGroup::addObjectToBack(RenderObject* obj){

    if(obj == nullptr){
        return;
    }

    RenderObjectContainer* r = new RenderObjectContainer(obj);

    if(this->lastObject == nullptr){
        this->firstObject = r;
    }
    else{
        this->lastObject->setNextObject(r);
    }

    this->lastObject = r;

    this->objectCount++;

}

RenderGroup::~RenderGroup(){

    RenderObjectContainer* current = this->firstObject;
    RenderObjectContainer* next;

    while(current != nullptr){
        current->deleteContainedObject();
        next = current->getNextObject();
        delete current;
        current = next;
    }
    
}

int RenderGroup::getListSize(){
    return this->objectCount;
}

void RenderGroup::remove(RenderObjectContainer* target, RenderObjectContainer* prev){

    if(target == nullptr){
        return;
    }

    if(prev == nullptr){
        this->firstObject = target->getNextObject();
    }
    else{
        prev->setNextObject(target);
    }
    
    if(target->getNextObject() == nullptr){
        this->lastObject = prev;
    }

    delete target;
    this->objectCount--;

}

RenderObjectContainer* RenderGroup::getFirstObject(){
    return this->firstObject;
}

RenderObjectContainer* RenderGroup::getLastObject(){
    return this->lastObject;
}

void RenderGroup::empty(){
    RenderObjectContainer* current = this->firstObject;
    RenderObjectContainer* next;

    while(current != nullptr){
        next = current->getNextObject();
        delete current;
        current = next;
    }

    this->firstObject = nullptr;
    this->lastObject = nullptr;

    this->objectCount = 0;
}