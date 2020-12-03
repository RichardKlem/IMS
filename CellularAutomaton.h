//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELLULARAUTOMATON_H
#define IMS_CELLULARAUTOMATON_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Cell.h"
#include "Matrix.h"

class CellularAutomaton {
private:
    Matrix<Cell> matrix;

public:
    Matrix<Cell> &getMatrix() {
        return matrix;
    }

    void setMatrix(Matrix<Cell> &m) {
        CellularAutomaton::matrix = m;
    }

    void initInfection(unsigned int kazdej_kolikatej_co_se_ma_nakazit) {
        srand((int) time(0)); // Set random seed
        unsigned int infected_count = round(matrix.size / kazdej_kolikatej_co_se_ma_nakazit);
        printf("Infecting randomly: %d cells\n", infected_count);
        for (int i = 0; i < infected_count; ++i) {
            int row = (int) (rand() % matrix.dim.first);
            int column = (int) (rand() % matrix.dim.second);
            CellularAutomaton::matrix[row][column].setState(1);
        }
    }

    CellularAutomaton(unsigned int x, unsigned int y): matrix{Matrix<Cell>(x, y)}{;
    };

    void dumpMatrixToFile() {
        ofstream file;
        file.open("matrix_dump.txt");
        for (int i = 0; i < matrix.dim.second; ++i) {
            for (int j = 0; j < matrix.dim.first; ++j) {
                file << matrix[j][i].getState();
            }
            file << endl;
        }
        file.close();
    }
    void initPosition() {
        for (int i = 0; i < matrix.dim.second; ++i) {
            for (int j = 0; j < matrix.dim.first; ++j) {
                matrix[j][i].setX(i);
                matrix[j][i].setY(j);
            }
        }
    }
};


#endif //IMS_CELLULARAUTOMATON_H
