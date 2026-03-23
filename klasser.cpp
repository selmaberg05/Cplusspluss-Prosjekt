#include "klasser.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

//Dete er ikke en vanlig funksjon, det er en constructor. Alltid heter det samme som klassen. lager et objekt.
Ship::Ship(std::vector<std::pair<int, int>> positions) {
    this->positions = positions;
    hitStatus = std::vector<bool>(positions.size(), false);
}

bool Ship::registerHit(int x, int y) {
    for (int i = 0; i < positions.size(); i++) {
        if (positions[i].first == x && positions[i].second == y) {
            hitStatus[i] = true;
            return true;
        }
    }
    return false;
}

bool Ship::isSunk() {
    for (int i = 0; i < hitStatus.size(); i++) {
        if (hitStatus[i] == false) {
            return false;
        }
    }
    return true;
}

Board::Board() {
    grid = std::vector<std::vector<char>>(10, std::vector<char>(10, '.'));
}

void Board::placeShip(std::vector<std::pair<int, int>> positions) {
    if (positions.size() != 3) {
        throw std::runtime_error("Ship is wrong size");
    }

    if (!(
        (positions[0].first == positions[1].first &&
         positions[1].first == positions[2].first)
        ||
        (positions[0].second == positions[1].second &&
         positions[1].second == positions[2].second)
    )) {
        throw std::runtime_error("Ship is not straight");
    }

    int x0 = positions[0].first;
    int x1 = positions[1].first;
    int x2 = positions[2].first;

    int y0 = positions[0].second;
    int y1 = positions[1].second;
    int y2 = positions[2].second;

    if (x0 == x1 && x1 == x2) {
        int minY = std::min({y0, y1, y2});
        int maxY = std::max({y0, y1, y2});

        if (maxY - minY != 2) {
            throw std::runtime_error("Ship is not continuous");
        }
    } else {
        int minX = std::min({x0, x1, x2});
        int maxX = std::max({x0, x1, x2});

        if (maxX - minX != 2) {
            throw std::runtime_error("Ship is not continuous");
        }
    }

    for (int i = 0; i < positions.size(); i++) {
        int x = positions[i].first;
        int y = positions[i].second;

        if (x < 0 || x >= 10 || y < 0 || y >= 10) {
            throw std::out_of_range("Ship is out of bounds");
        }

        if (grid[x][y] == 'S') {
            throw std::runtime_error("Ship overlaps another ship");
        }
    }

    Ship ship(positions);
    ships.push_back(ship);

    for (int i = 0; i < positions.size(); i++) {
        int x = positions[i].first;
        int y = positions[i].second;
        grid[x][y] = 'S';
    }
}

bool Board::shoot(int x, int y) {
    if ( x>=10 || x<0 || y>=10 || y<0 ){
        throw std::out_of_range("Shoot is out of bounds");
    }
    
    if (grid[x][y]=='X' || grid[x][y]=='O'){
        throw std::runtime_error("Already Shot");  
    }
    for (Ship& ship : ships) {
        if (ship.registerHit(x, y)) {
            grid[x][y] = 'X';
            return true;
        }
    }
     
    grid[x][y]='O';
        
    return false;
        
    
}

void Board::printBoard(bool showShips) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'S' && !showShips) {
                std::cout << ". ";
            } else {
                std::cout << grid[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}