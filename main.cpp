/**
 * @author1: Martin Haderka
 * @author2: Richard Klem
 * @email1: xhader00@stud.fit.vutbr.cz
 * @email2: xklemr00@stud.fit.vutbr.cz
 * @login1: xhader00
 * @login2: xklemr00
 * @date: 6.11.2020
 */
#include <iostream>
#include "CellularAutomaton.h"
#include "main.h"


int main(int argc, char *argv[]) {
    unsigned int x = 23, y = 23, step = 1, number = 60, initInfectionRate = 10, initImmuneRate = 20,
    forwardP = 20, rightP = 20, leftP = 20, backP = 20, stayP = 20;
    string dumpDir = "./";
    bool model2 = false;
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
        argParse(argc, argv, &number, &initInfectionRate, &initImmuneRate, &x, &y, &step, &forwardP, &rightP,
                 &leftP, &backP, &stayP, &dumpDir, &model2);

    CellularAutomaton CA(x, y, number, &walls);
    CA.initWalls(&CA.getMatrix());
    CA.initCellPositions();
    CA.initPersonPositions();
    CA.simulate(step, initInfectionRate, initImmuneRate, forwardP, rightP, leftP, backP, stayP, &dumpDir, model2);
    return 0;
}
