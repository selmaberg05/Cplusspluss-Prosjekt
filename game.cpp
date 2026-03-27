
#include "game.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

Game::Game() {
    shots = 0;
}

void Game::setUpShips() {
    setUpPlayerShips();
    placeRandomEnemyShips();
}

void Game::play() {
    while (!enemyBoard.allShipsSunk()) {
        std::string input;
        int x, y;

        std::cout << "\n Ditt brett: \n" << std::endl;
        playerBoard.printBoard(true);

        std::cout << "\n Fiendens brett \n" << std::endl;
        enemyBoard.printBoard(false);


        std::cout << "Antall skudd: " << shots << std::endl;
        std::cout << "Skriv inn x og y (eller . for å avslutte): ";
        std::cin >> input;

        if (input == ".") {
            std::cout << "Spillet ble avsluttet.\n";
            return;
        }

        try {
            x = std::stoi(input);

            if (!(std::cin >> y)) {
                throw std::runtime_error("Du må skrive inn to tall");
            }

            bool hit = enemyBoard.shoot(x, y);
            shots++;

            if (hit) {
                if (enemyBoard.shipSunkAt(x, y)) {
                    std::cout << "Treff! Du sank et skip!\n";
                } else {
                    std::cout << "Treff!\n";
                }
            } else {
                std::cout << "Bom!\n";
            }

            if (enemyBoard.allShipsSunk()) {
                break;
            }
            enemyTurn();

            if(playerBoard.allShipsSunk()){
                std::cout << "Alle skipene dine er sunket! Du tapte! \n";
                return;

            }
            
        }
        catch (std::exception& e) {
            std::cout << "Feil: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    std::cout << "Alle skip er sunket! Du vant på " << shots << " skudd!\n";
}


void Game::placeRandomEnemyShips() {
    std::srand(std::time(0));

    int shipsPlaced=0;

    while (shipsPlaced < 4) { //2 skip
        int x=rand() % 10; //gir tilfeldig tall fra 0 til 9. Gir tilfeldig startpunkt
        int y=rand() % 10;

        bool horizontal=rand() % 2; //gir 0 eller 1

        std::vector<std::pair<int, int>> positions;

        if (horizontal) {
            positions={{x, y}, {x+1, y}, {x+2, y}};
        } else {
            positions={{x, y}, {x, y+1}, {x, y+2}};
        }
        try {
            enemyBoard.placeShip(positions);
            shipsPlaced++;
        }
        catch (...) {
            //hvis det feiler, prøv igjen
        }
    }
}

bool Game::enemyAlreadyShot(int x, int y) {
    for (int i=0; i< enemyShots.size(); i++) {
        if (enemyShots[i].first==x && enemyShots[i].second== y) {
        }
    }
    return false;
}

void Game::enemyTurn() {
    int x, y;

    while (true) {
        x=rand() % 10;
        y=rand() % 10;

        if (!enemyAlreadyShot(x, y)) {
            enemyShots.push_back({x, y});
            break;
        }
    }
    std::cout << "fienden skyter på (" << x << ", " << y << "):";
    
    bool hit =playerBoard.shoot(x, y);

    if (hit) {
        if (playerBoard.shipSunkAt(x, y)){
            std::cout << "Treff! Fienden sank et av skipene dine! \n";
        } else {
            std::cout << "Tref! \n";
        }
    } else {
        std::cout << "Bom! \n";
    }
}

void Game::setUpPlayerShips() {
    int shipsPlaced=0;

    while (shipsPlaced< 4) {
        int x, y;
        char direction;

        std::cout << "\n Plasser skip" << shipsPlaced+1 << "av 4\n";
        playerBoard.printBoard(true);
        std::cout << "Skriv inn start-x og start-y og retning (h/v): ";

        std::cin >> x >> y >> direction;

        std::vector <std::pair<int, int>> positions;

        if (direction =='h') {
            positions={{x, y}, {x+1, y}, {x+2, y}};
        } else if (direction== 'v') {
            positions={{x, y}, {x, y+1}, {x, y+2}};
        } else {
            std::cout << "Du skrev feil, enten v eller h \n";
            continue;
        }
        try{
            playerBoard.placeShip(positions);
            shipsPlaced++;
        }
        catch (std::exception & e) {
            std::cout <<"Feil: " << e.what() << std::endl;
        }
    }
}