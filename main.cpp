#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <list>

using namespace std;

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void gotoXY(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void hideCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

void paintLimits() {
    for (int i = 2; i < 78; i++) {
        gotoXY(i, 3);
        printf("%c", 205);
        gotoXY(i, 33);
        printf("%c", 205);
    }

    for (int i = 4; i < 33; i++) {
        gotoXY(2, i);
        printf("%c", 186);
        gotoXY(77, i);
        printf("%c", 186);
    }

    gotoXY(2, 3);
    printf("%c", 201);
    gotoXY(2, 33);
    printf("%c", 200);
    gotoXY(77, 3);
    printf("%c", 187);
    gotoXY(77, 33);
    printf("%c", 188);
}

class Ship {
private:
    int x, y;
    int health;
    int lives;
public:
    Ship(int _x, int _y, int _health, int _lives)
            : x(_x), y(_y), health(_health), lives(_lives) {};

    int X() { return x; }

    int Y() { return y; }

    int getLives() { return lives; }

    void damage() { health--; }

    void paint();

    void clear();

    void move();

    void paintHealth();

    void death();
};

void Ship::paint() {
    gotoXY(x, y);
    printf("  %c", 30);
    gotoXY(x, y + 1);
    printf(" %c%c%c", 40, 207, 41);
    gotoXY(x, y + 2);
    printf("%c%c %c%c", 30, 190, 190, 30);
}

void Ship::clear() {
    gotoXY(x, y);
    printf("        ");
    gotoXY(x, y + 1);
    printf("        ");
    gotoXY(x, y + 2);
    printf("        ");
}

void Ship::move() {
    if (kbhit()) {
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
    }
}

void Ship::paintHealth() {
    gotoXY(50, 2);
    printf("Lives %d", lives);
    gotoXY(64, 2);
    printf("Health ");
    gotoXY(70, 2);
    printf("         ");
    for (int i = 0; i < health; i++) {
        gotoXY(70 + i, 2);
        printf("%c", 3);
    }
}

void Ship::death() {
    if (health == 0) {
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
    }
}

class Asteroid {
private:
    int x, y;
public:
    Asteroid(int _x, int _y) : x(_x), y(_y) {};

    int X() { return x; }

    int Y() { return y; }

    void paint();

    void move();

    void clash(class Ship &ship);
};

void Asteroid::paint() {
    gotoXY(x, y);
    printf("%c", 184);
}

void Asteroid::move() {
    gotoXY(x, y);
    printf(" ");
    y++;
    if (y > 32) {
        x = rand() % 71 + 4;
        y = 4;
    }
    paint();
}

void Asteroid::clash(class Ship &ship) {
    if (x >= ship.X()
        && x < ship.X() + 6
        && y >= ship.Y()
        && y <= ship.Y() + 2) {
        ship.damage();
        ship.clear();
        ship.paint();
        ship.paintHealth();
        x = rand() % 71 + 4;
        y = 4;
    }
}

class Bullet {
private:
    int x, y;
public:
    Bullet(int _x, int _y) : x(_x), y(_y) {};

    int X() { return x; }

    int Y() { return y; }

    void move();

    bool out();
};

void Bullet::move() {
    gotoXY(x, y);
    printf(" ");
    y--;
    gotoXY(x, y);
    printf("*");
}

bool Bullet::out() {
    if (y == 4) return true;
    return false;
}

int main() {
    hideCursor();
    paintLimits();
    Ship ship(37, 30, 3, 3);
    ship.paint();
    ship.paintHealth();

    list<Asteroid *> listAsteroid;
    list<Asteroid *>::iterator indexAsteroid;

    for (int i = 0; i < 5; i++) {
        listAsteroid.push_back(new Asteroid(rand() % 74 + 3, rand() % 5 + 4));
    }

    list<Bullet *> listBullet;
    list<Bullet *>::iterator indexBullet;

    bool game_over = false;

    int score = 0;
    while (!game_over) {

        gotoXY(4, 2);
        printf("Score %d", score);
        if (kbhit()) {
            int key = getch();
            if (key == 'a') {
                listBullet.push_back(new Bullet(ship.X() + 2, ship.Y() - 1));
            }
        }

        for (indexBullet = listBullet.begin();
             indexBullet != listBullet.end();
             indexBullet++) {
            (*indexBullet)->move();
            if ((*indexBullet)->out()) {
                gotoXY((*indexBullet)->X(), (*indexBullet)->Y());
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
                if ((*indexBullet)->X() == (*indexAsteroid)->X() &&
                    ((*indexAsteroid)->Y() + 1 == (*indexBullet)->Y()
                     || (*indexAsteroid)->Y() == (*indexBullet)->Y())) {
                    gotoXY((*indexBullet)->X(), (*indexBullet)->Y());
                    printf(" ");
                    delete (*indexBullet);
                    indexBullet = listBullet.erase(indexBullet);

                    listAsteroid.push_back(new Asteroid(rand() % 74 + 3, 4));
                    gotoXY((*indexAsteroid)->X(), (*indexAsteroid)->Y());
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
