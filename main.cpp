#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <list>
#include "lib/Engine.h"
#include "lib/Ship.h"
#include "lib/Asteroid.h"
#include "lib/Bullet.h"

using namespace std;

void gotoXY(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

int main() {
    Engine engine;
    Ship ship(37, 30, 3, 3);
    ship.paint();
    ship.paintHealth();
    list<Asteroid *> listAsteroid;
    list<Asteroid *>::iterator indexAsteroid;

    list<Bullet *> listBullet;
    list<Bullet *>::iterator indexBullet;

    for (int i = 0; i < 5; i++) {
        listAsteroid.push_back(new Asteroid(rand() % 74 + 3, rand() % 5 + 4));
    }
    bool game_over = false;

    int score = 0;
    while (!game_over) {

        gotoXY(4, 2);
        printf("Score %d", score);

        if (kbhit()) {
            int key = getch();
            if (key == 'a') {
                listBullet.push_back(new Bullet(ship.getX() + 2, ship.getY() - 1));
            }
        }

        for (indexBullet = listBullet.begin();
             indexBullet != listBullet.end();
             indexBullet++) {
            (*indexBullet)->move();
            if ((*indexBullet)->out()) {
                gotoXY((*indexBullet)->getX(), (*indexBullet)->getY());
                printf(" ");
                delete (*indexBullet);
                indexBullet = listBullet.erase(indexBullet);
            }
        }

        for (indexAsteroid = listAsteroid.begin();
             indexAsteroid != listAsteroid.end();
             indexAsteroid++) {
            (*indexAsteroid)->move();
            (*indexAsteroid)->clash(ship);
        }

        for (indexAsteroid = listAsteroid.begin();
             indexAsteroid != listAsteroid.end();
             indexAsteroid++) {
            for (indexBullet = listBullet.begin();
                 indexBullet != listBullet.end();
                 indexBullet++) {
                if ((*indexBullet)->getX() == (*indexAsteroid)->getX() &&
                    ((*indexAsteroid)->getY() + 1 == (*indexBullet)->getY()
                     || (*indexAsteroid)->getY() == (*indexBullet)->getY())) {
                    gotoXY((*indexBullet)->getX(), (*indexBullet)->getY());
                    printf(" ");
                    delete (*indexBullet);
                    indexBullet = listBullet.erase(indexBullet);

                    listAsteroid.push_back(new Asteroid(rand() % 74 + 3, 4));
                    gotoXY((*indexAsteroid)->getX(), (*indexAsteroid)->getY());
                    printf(" ");
                    delete (*indexAsteroid);
                    indexAsteroid = listAsteroid.erase(indexAsteroid);

                    score += 5;
                }
            }
        }

        if (ship.getLives() == 0) {
            game_over = true;
        }
        ship.death();
        ship.move();

        Sleep(30);
    }
    return 0;
}
