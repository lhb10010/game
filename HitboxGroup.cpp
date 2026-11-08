#include "HitboxGroup.h"
#include <iostream>
#include "PhysicsBox.h"


HitboxObjectContainer::HitboxObjectContainer(PhysicsBox* obj){
    this->object = new PhysicsBox*[1];
    *object = obj;
    this->nextObject = nullptr;
}

PhysicsBox** HitboxObjectContainer::getObjectPointer(){
    return object;
}

void HitboxObjectContainer::setNextObject(HitboxObjectContainer* obj){
    this->nextObject = obj;
}

HitboxObjectContainer* HitboxObjectContainer::getNextObject(){
    return this->nextObject;
}

PhysicsBox* HitboxObjectContainer::getObject(){
    return *object;
}

void HitboxObjectContainer::deleteContainedObject(){
    PhysicsBox* temp = *object;
    delete temp;
    *object = nullptr;
}

HitboxObjectContainer::~HitboxObjectContainer(){
    PhysicsBox** pointer = object;
    delete pointer;
}




HitboxGroup::HitboxGroup(std::vector<PhysicsBox*> objects){

    if(objects.size() < 1){
        this->lastObject = nullptr;
        this->firstObject = nullptr;
        this->objectCount = 0;
    }

    HitboxObjectContainer* first = new HitboxObjectContainer(objects.at(0));
    this->firstObject = first;
    this->objectCount = objects.size();

    HitboxObjectContainer* last = first;
    HitboxObjectContainer* current;

    for(int i = 1; i < objects.size(); i++){
        current = new HitboxObjectContainer(objects.at(i));
        last->setNextObject(current);
        last = current;
    }

    this->lastObject = last;

}

HitboxGroup::HitboxGroup(){
    this->lastObject = nullptr;
    this->firstObject = nullptr;
    this->objectCount = 0;
}

void HitboxGroup::addObjectToFront(PhysicsBox* obj){

    if(obj == nullptr){
        return;
    }

    HitboxObjectContainer* r = new HitboxObjectContainer(obj);
    
    if(this->firstObject == nullptr){
        this->lastObject = r;
    }
        
    r->setNextObject(this->firstObject);
    this->firstObject = r;
    
    this->objectCount++;

}

void HitboxGroup::addObjectToBack(PhysicsBox* obj){

    if(obj == nullptr){
        return;
    }

    HitboxObjectContainer* r = new HitboxObjectContainer(obj);

    if(this->lastObject == nullptr){
        this->firstObject = r;
    }
    else{
        this->lastObject->setNextObject(r);
    }

    this->lastObject = r;

    this->objectCount++;

}

HitboxGroup::~HitboxGroup(){

    HitboxObjectContainer* current = this->firstObject;
    HitboxObjectContainer* next;

    while(current != nullptr){
        current->deleteContainedObject();
        next = current->getNextObject();
        delete current;
        current = next;
    }
    
}

int HitboxGroup::getListSize(){
    return this->objectCount;
}

void HitboxGroup::remove(HitboxObjectContainer* target, HitboxObjectContainer* prev){

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

HitboxObjectContainer* HitboxGroup::getFirstObject(){
    return this->firstObject;
}

HitboxObjectContainer* HitboxGroup::getLastObject(){
    return this->lastObject;
}

void HitboxGroup::empty(){
    HitboxObjectContainer* current = this->firstObject;
    HitboxObjectContainer* next;

    while(current != nullptr){
        next = current->getNextObject();
        delete current;
        current = next;
    }

    this->firstObject = nullptr;
    this->lastObject = nullptr;

    this->objectCount = 0;
}