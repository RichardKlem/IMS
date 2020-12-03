#include <iostream>
#ifdef __linux__
#include <getopt.h>
#endif
#include "CellularAutomaton.h"
#include "my_string.h"
#include "main.h"


int main(int argc, char *argv[]) {
    unsigned int initInfectionRate = 0;

    if (argc > 1)
        argParse(argc, argv, &initInfectionRate);

    CellularAutomaton CA(3, 3);
    CA.getMatrix()[2][2].setState(1);
    //cout << CA.getMatrix().size / initInfectionRate << endl;
    CA.initPosition();
    //CA.dumpMatrixToFile();

    //std::cout << "Hello, World! " << std::endl << CA.getMatrix()[2][2].getState() << std::endl << CA.getMatrix()[2][2].getState();
    return 0;
}
