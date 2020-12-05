#include <iostream>
#ifdef __linux__
#include <getopt.h>
#endif
#include "CellularAutomaton.h"
#include "my_string.h"
#include "main.h"


int main(int argc, char *argv[]) {
    unsigned int x = 23, y = 23, time = 10, step = 2, number = 60, initInfectionRate = 10, initImmuneRate = 5,
    forwardP = 25, rightP = 25, leftP = 25, backP = 25, stayP = 0;
    vector<pair<unsigned int, unsigned int>> walls {{17, 0}, {17, 1}, {17, 2}, {17, 3},
                                                    {17, 4}, {17, 5}, {17, 6}, {18, 6},
                                                    {19, 6},

                                                    {0, 11}, {1, 11}, {2, 11}, {3, 11},
                                                    {4, 11}, {5, 11}, {6, 11}, {7, 11},
                                                    {8, 11}, {9, 11}, {10, 11}, {11, 11},
                                                    {12, 11}, {13, 11}, {14, 11}, {15, 11},
                                                    {16, 11}, {17, 11}, {17, 12}, {17, 13},
                                                    {17, 14}, {17, 15}, {17, 16}, {17, 17},
                                                    {17, 18}};
    if (argc > 1)
        argParse(argc, argv, &number, &initInfectionRate, &initImmuneRate, &x, &y, &time, &step);

    CellularAutomaton CA(x, y, number, &walls);
    CA.initWalls(&CA.getMatrix());
    CA.initCellPositions();
    CA.initPersonPositions();
    CA.simulate(time, step, initInfectionRate, initImmuneRate, forwardP, rightP, leftP, backP, stayP);
    return 0;
}
