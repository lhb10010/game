#include <string>
#include <vector>

#ifndef RENDEREROBJECT_H
#define RENDEREROBJECT_H


class RenderObject{

    public:
        int getXPos();
        int getYPos();
        int getWidth();
        int getHeight();
        virtual std::string getTextureName();
        RenderObject(int x, int y, int w, int h, std::string texture);
        //RenderObject(int x, int y, int w, int h, std::string texture, bool isGroup);
        std::vector<int> getErrorColor();
        bool hasSubObjects();
        virtual std::vector<RenderObject*> getSubObjects();
        bool isPosAbsolute();
        RenderObject(int x, int y, int w, int h, std::string texture, bool isAbsolute);
        RenderObject(int x, int y, int w, int h, std::string texture, bool isAbsolute, bool isGroup);
        bool isVisible();
        void setVisible(bool visible);
        void setSubObjects(std::vector<RenderObject*> vec);
        bool usingGroup();
        void setUsingGroup(bool isGroup);
        void setTexture(std::string texture);
        std::vector<int> getCenter();

        void moveX(int x);
        void moveY(int y);
        void setX(int x);
        void setY(int y);

        int getAbsoluteX();
        int getAbsoluteY();

        ~RenderObject();

        void setDoublePointer(RenderObject** dp);

    protected:
        long id;

        RenderObject** doubleP;

        int xPos;
        int yPos;
        int width;
        int height;
        int xAbsolutePos;
        int yAbsolutePos;
        std::string texture;
        bool absolutePos;
        bool visible;
        bool isGroup;

        std::vector<int> errorColor;
        

    //private:

        std::vector<RenderObject*> subObjects;
        

};

#endif