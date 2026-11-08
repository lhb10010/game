#include <vector>
#include "RenderObject.h"


#ifndef RENDERGROUP_H
#define RENDERGROUP_H


class RenderObjectContainer{

    public:
        RenderObjectContainer(RenderObject* obj);
        RenderObjectContainer* getNextObject();
        RenderObject** getObjectPointer();
        RenderObject* getObject();
        void setNextObject(RenderObjectContainer* obj);
        ~RenderObjectContainer();
        void deleteContainedObject();

    private:
        RenderObject** object;
        RenderObjectContainer* nextObject;

};


class RenderGroup{

    public:
        RenderGroup();
        RenderGroup(std::vector<RenderObject*> objects);
        RenderObjectContainer* getFirstObject();
        RenderObjectContainer* getLastObject();
        void addObjectToFront(RenderObject* obj);
        void addObjectToBack(RenderObject* obj);
        ~RenderGroup();
        int getListSize();
        void remove(RenderObjectContainer* target, RenderObjectContainer* prev);
        void empty();

    private:
        int objectCount;
        RenderObjectContainer* lastObject;
        RenderObjectContainer* firstObject;

};


#endif