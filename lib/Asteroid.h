//
// Created by rodolfo_pc on 6/6/2021.
//

#ifndef SHIP_ASTEROID_H
#define SHIP_ASTEROID_H


#include "Engine.h"

class Asteroid : public Engine {
private:
    int x, y;
public:
    Asteroid(int _x, int _y) : x(_x), y(_y) {};

    int getX() { return x; }

    int getY() { return y; }

    void paint();

    void move();

    void clash(class Ship &ship);
};


#endif //SHIP_ASTEROID_H
