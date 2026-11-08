#include <vector>
#include "PhysicsBox.h"


#ifndef HITBOXGROUP_H
#define HITBOXGROUP_H

class PhysicsBox;


class HitboxObjectContainer{

    public:
        HitboxObjectContainer(PhysicsBox* obj);
        HitboxObjectContainer* getNextObject();
        PhysicsBox** getObjectPointer();
        PhysicsBox* getObject();
        void setNextObject(HitboxObjectContainer* obj);
        ~HitboxObjectContainer();
        void deleteContainedObject();

    private:
        PhysicsBox** object;
        HitboxObjectContainer* nextObject;

};


class HitboxGroup{

    public:
        HitboxGroup();
        HitboxGroup(std::vector<PhysicsBox*> objects);
        HitboxObjectContainer* getFirstObject();
        HitboxObjectContainer* getLastObject();
        void addObjectToFront(PhysicsBox* obj);
        void addObjectToBack(PhysicsBox* obj);
        ~HitboxGroup();
        int getListSize();
        void remove(HitboxObjectContainer* target, HitboxObjectContainer* prev);
        void empty();

    private:
        int objectCount;
        HitboxObjectContainer* lastObject;
        HitboxObjectContainer* firstObject;

};


#endif