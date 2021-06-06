//
// Created by rodolfo_pc on 5/6/2021.
//

#ifndef SHIP_SHIP_H
#define SHIP_SHIP_H

#include "Engine.h"

class Ship : public Engine {
private:
    int x, y;
    int health;
    int lives;
public:
    Ship(int _x, int _y, int _health, int _lives);

    int getX() { return x; }

    int getY() { return y; }

    int getLives() { return lives; }

    void damage() { health--; }

    void paint();

    void clear();

    void move();

    void paintHealth();

    void death();
};


#endif //SHIP_SHIP_H
