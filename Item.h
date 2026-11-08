#ifndef ITEM_H
#define ITEM_H

#include <string>
class RenderObject;

class Item{

    public:
        Item(std::string name, std::string texture);
        std::string getTexture();
        bool equals(Item* i);
        std::string getName();
        RenderObject* makeRenderObject(int x, int y, int width, int height, bool absolutePos);

        /*
        bool operator==(const Item& other) const {
            return name == other.name;
        }
            */

    private:
        std::string name;
        std::string texture;

};

#endif