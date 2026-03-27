#pragma once
#include "klasser.h"

class Game {
private:
    Board playerBoard;
    Board enemyBoard;
    int shots;
    std::vector<std::pair<int, int>> enemyShots;



public:
    Game();
    void setUpShips();
    void placeRandomEnemyShips();
    void enemyTurn();
    bool enemyAlreadyShot(int x, int y);
    void setUpPlayerShips();
    void play();

};