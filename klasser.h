#pragma once
#include <vector>
#include <utility>

class Ship {
private:
    std::vector<std::pair<int, int>> positions;
    std::vector<bool> hitStatus;

public:
    Ship(std::vector<std::pair<int, int>> positions);
    bool registerHit(int x, int y);
    bool isSunk();
    bool occupiesPosition(int x, int y);
};

class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<Ship> ships;

public:
    Board();
    void placeShip(std::vector<std::pair<int, int>> positions);
    bool shoot(int x, int y);
    void printBoard(bool showShips);
    bool allShipsSunk();
};

