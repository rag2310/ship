//
// Created by rodolfo_pc on 6/6/2021.
//

#ifndef SHIP_BULLET_H
#define SHIP_BULLET_H


#include "Engine.h"

class Bullet : public Engine {
private:
    int x, y;
public:
    Bullet(int _x, int _y) : x(_x), y(_y) {};

    int getX() { return x; }

    int getY() { return y; }

    void move();

    bool out();
};


#endif //SHIP_BULLET_H
