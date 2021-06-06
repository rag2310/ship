//
// Created by rodolfo_pc on 5/6/2021.
//

#include "Engine.h"
#include "Ship.h"
#include <cstdio>
#include <windows.h>
#include <list>

using namespace std;

Engine::Engine() {
    this->hideCursor();
    this->paintWorld();
};

void Engine::hideCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

void Engine::goToXY(int x, int y) const {

    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = (SHORT) x;
    dwPos.Y = (SHORT) y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void Engine::paintWorld() {
    //height = 35
    //width = 80
    for (int i = 2; i < 78; i++) {
        goToXY(i, 3);
        printf("%c", 205);
        goToXY(i, 33);
        printf("%c", 205);
    }

    for (int i = 4; i < 33; i++) {
        goToXY(2, i);
        printf("%c", 186);
        goToXY(77, i);
        printf("%c", 186);
    }

    goToXY(2, 3);
    printf("%c", 201);
    goToXY(2, 33);
    printf("%c", 200);
    goToXY(77, 3);
    printf("%c", 187);
    goToXY(77, 33);
    printf("%c", 188);
}