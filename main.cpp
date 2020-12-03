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

    CellularAutomaton CA(50, 50);
    //CA.getMatrix()[1][1].setState(1);
    CA.initPosition();
    CA.simulate(5, initInfectionRate);
    //std::cout << "Hello, World! " << std::endl << CA.getMatrix()[2][2].getState() << std::endl << CA.getMatrix()[2][2].getState();
    return 0;
}
