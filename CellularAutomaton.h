//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELLULARAUTOMATON_H
#define IMS_CELLULARAUTOMATON_H

#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

class CellularAutomaton {
private:
    Matrix matrix;

public:
    Matrix &getMatrix() {
        return matrix;
    }

    void setMatrix(Matrix &m) {
        CellularAutomaton::matrix = m;
    }

    void initInfection(unsigned int kazdej_kolikatej_co_se_ma_nakazit) {
        srand((int) time(0)); // Set random seed
        unsigned int infected_count = round(matrix.size/kazdej_kolikatej_co_se_ma_nakazit);
        printf("Infecting randomly: %d cells\n", infected_count);
        for (int i = 0; i < infected_count; ++i) {
            int row = (int)(rand() % matrix.dim.first);
            int column = (int)(rand() % matrix.dim.second);
            CellularAutomaton::matrix[row][column].setState(1);
        }
    }

    CellularAutomaton(unsigned int x, unsigned int y): matrix{Matrix(x, y)}{;
    };
};


#endif //IMS_CELLULARAUTOMATON_H
