#include <iostream>

#include "CellularAutomaton.h"

int main() {
    CellularAutomaton CA(12, 12);

    CA.initInfection(10);

    CA.getMatrix()[10][10].setState(1);

    CA.dumpMatrixToFile();

    std::cout << "Hello, World! " << std::endl << CA.getMatrix()[10][10].getState() << std::endl << CA.getMatrix()[10][11].getState();
    return 0;
}
