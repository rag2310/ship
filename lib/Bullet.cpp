//
// Created by rodolfo_pc on 6/6/2021.
//

#include <cstdio>
#include "Bullet.h"

void Bullet::move() {
    goToXY(x, y);
    printf(" ");
    y--;
    goToXY(x, y);
    printf("*");
}

bool Bullet::out() {
    if (y == 4) return true;
    return false;
}