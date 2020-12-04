#include <iostream>
#ifdef __linux__
#include <getopt.h>
#endif
#include "CellularAutomaton.h"
#include "my_string.h"
#include "main.h"


int main(int argc, char *argv[]) {
    unsigned int initInfectionRate = 1000, x = 40, y = 60, time = 50, step = 1;

    if (argc > 1)
        argParse(argc, argv, &initInfectionRate, &x, &y, &time, &step);

    CellularAutomaton CA(x, y);
    CA.initPosition();
    CA.simulate(time, initInfectionRate);
    return 0;
}
