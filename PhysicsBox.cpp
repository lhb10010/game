#include "PhysicsBox.h"
#include "RenderObject.h"
#include <iostream>


PhysicsBox::PhysicsBox(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}


bool PhysicsBox::overLap(PhysicsBox* p){

    return overLap(p, 0, 0);

}


bool PhysicsBox::overLap(PhysicsBox* p, int incX, int incY){

    int pX1 = p->x + incX;
    int pX2 = p->x + incX + p->width;
    int oX1 = this->x;
    int oX2 = this->x + this->width;
    int pY1 = p->y + incY;
    int pY2 = p->y + incY + p->height;
    int oY1 = this->y;
    int oY2 = this->y + this->height;

    std::cout << "pX1=" << pX1 << " pX2=" << pX2
          << " oX1=" << oX1 << " oX2=" << oX2
          << " pY1=" << pY1 << " pY2=" << pY2
          << " oY1=" << oY1 << " oY2=" << oY2
          << std::endl;

    std::cout << "start\n";
    if((pX1 >= oX1 && pX1 <= oX2) || (pX2 >= oX1 && pX2 <= oX2) || (pX1 <= oX1 && pX2 >= oX2) || (oX1 <= pX1 && oX2 >= pX2)){
        std::cout << "pass1\n";
        if((pY1 >= oY1 && pY1 <= oY2) || (pY2 >= oY1 && pY2 <= oY2) || (pY1 <= oY1 && pY2 >= oY2) || (oY1 <= pY1 && oY2 >= pY2)){
            std::cout << "pass2\n";
            return true;
        }
    }


    return false;

}

void PhysicsBox::setX(int x){
    this->x = x;
}
void PhysicsBox::setY(int y){
    this->y = y;
}

void PhysicsBox::xMove(int x){
    this->x += x;
    if(RenderObject* d = dynamic_cast<RenderObject*>(this)){
        d->setX(this->x);
        std::cout << "xMove\n";
    }
}
void PhysicsBox::yMove(int y){
    this->y += y;
    if(RenderObject* d = dynamic_cast<RenderObject*>(this)){
        d->setY(this->y);
    }
}


bool PhysicsBox::checkType(int type){
    for(int i = 0; i < this->types.size(); i++){
        if(types.at(i) == type){
            return true;
        }
    }
    return false;
}


std::vector<int> PhysicsBox::getMovement(){
    return {this->nextX, this->nextY};
}