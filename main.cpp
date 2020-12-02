#include <iostream>
#include "CelluarAtomaton.h"
#include "Matrix.h"

int main() {
    // Example usage
    Matrix mm(100,100);

    mm[10][10].setState(1);

    std::cout << "Hello, World! " << std::endl << mm[10][10].getState() << mm[10][9].getState();
    return 0;
}
