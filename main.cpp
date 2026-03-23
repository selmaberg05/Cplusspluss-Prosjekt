#include "klasser.h"
#include <iostream>

int main() {
    Board board;

    //legg inn et skip
    board.placeShip({{1,3}, {1,4}, {1,5}});

    //print med skip synlig
    std::cout << "Mitt brett:\n";
    board.printBoard(true);

    std::cout << std::endl;

    //skyter
    bool result1=board.shoot(1,3);
    bool result2=board.shoot(0, 0);

    //print igjen
    std::cout << "Etter skudd:\n";
    std::cout << result1 << std::endl;
    std::cout << result2 << std:: endl;
    
    board.printBoard(true);

    return 0;
}
