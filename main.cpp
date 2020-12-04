#include <iostream>
#ifdef __linux__
#include <getopt.h>
#endif
#include "CellularAutomaton.h"
#include "my_string.h"
#include "main.h"


int main(int argc, char *argv[]) {
    unsigned int initInfectionRate = 5, x = 6, y = 8, time = 5, step = 1;

    if (argc > 1)
        argParse(argc, argv, &initInfectionRate, &x, &y, &time, &step);

    const vector<pair<unsigned int, unsigned int>> walls {{0,3},{1,3}, {2,3}, {3,3}, {4,3}};
    CellularAutomaton CA(x, y, 10, &walls);
    CA.initWalls(&CA.getMatrix());
    CA.initCellPositions();
    CA.initPersonPositions();
    CA.simulate(time, initInfectionRate, step);
    return 0;
}
