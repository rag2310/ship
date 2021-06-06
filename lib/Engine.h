//
// Created by rodolfo_pc on 5/6/2021.
//

#include <list>

using namespace std;

#ifndef SHIP_ENGINE_H
#define SHIP_ENGINE_H

class Engine {
private:
    void paintWorld();

    void hideCursor();

public:
    Engine();

    void goToXY(int x, int y) const;

};


#endif //SHIP_ENGINE_H
