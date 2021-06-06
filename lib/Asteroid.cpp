//
// Created by rodolfo_pc on 6/6/2021.
//

#include <cstdlib>
#include <cstdio>
#include "Asteroid.h"
#include "Ship.h"

void Asteroid::paint() {
    goToXY(x, y);
    printf("%c", 184);
}

void Asteroid::move() {
    goToXY(x, y);
    printf(" ");
    y++;
    if (y > 32) {
        x = rand() % 71 + 4;
        y = 4;
    }
    paint();
}

void Asteroid::clash(class Ship &ship) {
    if (x >= ship.getX()
        && x < ship.getX() + 6
        && y >= ship.getY()
        && y <= ship.getY() + 2) {
        ship.damage();
        ship.clear();
        ship.paint();
        ship.paintHealth();
        x = rand() % 71 + 4;
        y = 4;
    }
}
