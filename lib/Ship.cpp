//
// Created by rodolfo_pc on 5/6/2021.
//

#include "Ship.h"
#include <conio.h>
#include <cstdio>
#include <synchapi.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

Ship::Ship(int _x, int _y, int _health, int _lives) {
    x = _x;
    y = _y;
    health = _health;
    lives = _lives;
}

void Ship::move() {
    if (kbhit()) {
        int key = getch();
        clear();
        //printf(" ");
        if (key == LEFT && x > 3) x--;
        if (key == RIGHT && x + 6 < 77) x++;
        if (key == UP && y > 4) y--;
        if (key == DOWN && y + 3 < 33) y++;
        if (key == 'e') health--;
        paint();
        paintHealth();
    }
}

void Ship::clear() {

    goToXY(x, y);
    printf("        ");
    goToXY(x, y + 1);
    printf("        ");
    goToXY(x, y + 2);
    printf("        ");
}

void Ship::paint() {
    goToXY(x, y);
    printf("  %c", 3);
    goToXY(x, y + 1);
    printf(" %c%c%c", 40, 207, 41);
    goToXY(x, y + 2);
    printf("%c%c %c%c", 30, 190, 190, 30);
}

void Ship::paintHealth() {
    goToXY(50, 2);
    printf("Lives %d", lives);
    goToXY(64, 2);
    printf("Health");
    goToXY(70, 2);
    printf("         ");
    for (int i = 0; i < health; i++) {
        goToXY(70 + i, 2);
        printf("%c", 3);
    }
}

void Ship::death() {
    if (health == 0) {
        clear();
        goToXY(x, y);
        printf("   **   ");
        goToXY(x, y + 1);
        printf("  ****  ");
        goToXY(x, y + 2);
        printf("   **   ");
        Sleep(200);
        clear();
        goToXY(x, y);
        printf(" * ** *");
        goToXY(x, y + 1);
        printf("  **** ");
        goToXY(x, y + 2);
        printf(" * ** *");
        Sleep(200);
        clear();
        lives--;
        health = 3;
        paintHealth();
        paint();
    }
}
/*
void Ship::clear() {
    *//* gotoXY(x, y);
     printf("        ");
     gotoXY(x, y + 1);
     printf("        ");
     gotoXY(x, y + 2);
     printf("        ");*//*
}

void Ship::move() {
    *//* if (kbhit()) {
         int key = getch();
         clear();
         printf(" ");
         if (key == LEFT && x > 3) x--;
         if (key == RIGHT && x + 6 < 77) x++;
         if (key == UP && y > 4) y--;
         if (key == DOWN && y + 3 < 33) y++;
         if (key == 'e') health--;
         paint();
         paintHealth();
     }*//*
}

void Ship::paintHealth() {
    *//* gotoXY(50, 2);
     printf("Lives %d", lives);
     gotoXY(64, 2);
     printf("Health ");
     gotoXY(70, 2);
     printf("         ");
     for (int i = 0; i < health; i++) {
         gotoXY(70 + i, 2);
         printf("%c", 3);
     }*//*
}

void Ship::death() {
    *//* if (health == 0) {
         clear();
         gotoXY(x, y);
         printf("   **   ");
         gotoXY(x, y + 1);
         printf("  ****  ");
         gotoXY(x, y + 2);
         printf("   **   ");
         Sleep(200);
         clear();
         gotoXY(x, y);
         printf(" * ** *");
         gotoXY(x, y + 1);
         printf("  **** ");
         gotoXY(x, y + 2);
         printf(" * ** *");
         Sleep(200);
         clear();
         lives--;
         health = 3;
         paintHealth();
         paint();
     }*//*
}*/
