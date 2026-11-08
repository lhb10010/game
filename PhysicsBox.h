#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <vector>

class PhysicsBox{

    public:
        static void init();

        PhysicsBox(int x, int y, int width, int height);

        virtual bool overLap(PhysicsBox* p);
        bool overLap(PhysicsBox* p, int incX, int incY);
        bool checkType(int type);

        void setX(int x);
        void setY(int y);
        void xMove(int x);
        void yMove(int y);

        virtual std::vector<int> getMovement();

        static const int PLAYER_HIT_BOX = 1;
        static const int PLAYER_MOVE_BOX = 2;
        static const int PLAYER_ATTACK_BOX = 3;
        static const int ENEMY_HIT_BOX = 4;
        static const int ENEMY_ATTACK_BOX = 5;
        static const int ENEMY_MOVE_BOX = 6;

    protected:
        int nextX;
        int nextY;

    private:
        int x;
        int y;
        int width;
        int height;
        std::vector<int> types;



};

#endif