#include <vector>
#include <string>
#ifndef INTERFACE_H
#define INTERFACE_H

#include "RenderObject.h"

class Interface : public RenderObject{

    public:
        Interface(int x, int y, int width, int height, std::string texture);

    private:
        int screenX;
        int screenY;
        int screenWidth;
        int screenHeight;


};

#endif