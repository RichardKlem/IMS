#include <iostream>
#include "CellularAutomaton.h"

int main() {
    CellularAutomaton CA(100, 100);

    CA.getMatrix()[10][10].setState(1);

    std::cout << "Hello, World! " << std::endl << CA.getMatrix()[10][10].getState() << std::endl << CA.getMatrix()[10][11].getState();
    return 0;
}
