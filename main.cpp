#include "klasser.h"
#include <iostream>

int main() {
    Board board;

    //legg inn et skip
    board.placeShip({{1,1}, {1,2}, {1,3}});
    board.placeShip({{4, 4}, {5,4}, {6,4}});

    while (board.allShipsSunk()==false) {
        std::string input;
        int x, y;
        

        board.printBoard(false);
        std::cout << "Skriv inn x og y (eller . for å avslutte):";
        std::cin >> input;

        if (input == ".") {
            std::cout << "Spillet ble avsluttet. \n" ;
            return 0;
        }
    
        try {
            x=std::stoi(input);
            std::cin >> y;

            bool hit=board.shoot(x, y);

            if (hit) {
                std::cout<< "treff! \n";
            } else {
                std::cout<< "Bom! \n";        
            }
        }
        catch (std:: exception& e) {
            std::cout << "feil" << e.what() << std::endl;

            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    std::cout << "alle skip er sunket! Du vant! \n ";
    return 0;
}


 