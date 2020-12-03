//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELLULARAUTOMATON_H
#define IMS_CELLULARAUTOMATON_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Matrix.h"
#include "Cell.h"


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

    void initInfection(unsigned int infectionRatio, unsigned int ** newStates) {
        srand((int) time(nullptr)); // Set random seed
        unsigned int infectedCount = round((double)matrix.size / infectionRatio);
        if (infectedCount == 0)
            infectedCount = 1;
        printf("Infecting randomly: %d cells\n", infectedCount);
        for (int i = 0; i < infectedCount; ++i) {
            auto row = (unsigned int) (rand() % matrix.dim.first);
            auto column = (unsigned int) (rand() % matrix.dim.second);
            CellularAutomaton::matrix[row][column].setState(1);
            newStates[row][column] = 1;
        }
    }

    CellularAutomaton(unsigned int x, unsigned int y): matrix{Matrix<Cell>(x, y)}{;
    };

    void dumpMatrixToFile(unsigned int time) {
        ofstream file;
        string fileName = "matrix_dump" + to_string(time) + ".txt";
        file.open(fileName);
        for (int i = 0; i < matrix.dim.first; ++i) {
            for (int j = 0; j < matrix.dim.second; ++j) {
                file << matrix[i][j].getState();
            }
            file << endl;
        }
        file.close();
    }
    /**
     * Inicalizuje atributy bun
     */
    void initPosition() {
        for (int i = 0; i < matrix.dim.first; ++i) {
            for (int j = 0; j < matrix.dim.second; ++j) {
                matrix[i][j].setX(i);
                matrix[i][j].setY(j);
                matrix[i][j].initNeighbours();
            }
        }
    }

    void simulate(const unsigned int time, unsigned int infectionRatio) {
        static bool run = false;
        static unsigned int **newStates;
        if (!run){
            newStates = new unsigned int *[matrix.dim.first];
            for(int i = 0; i < matrix.dim.first; ++i){
                    newStates[i] = new unsigned int[matrix.dim.second]{0};
            }
            initInfection(infectionRatio, newStates);
            run = true;
            dumpMatrixToFile(0);
        }

        for (int t = 0; t < time; ++t) {
            for (int i = 0; i < matrix.dim.first; ++i) {
                for (int j = 0; j < matrix.dim.second; ++j) {
                    matrix[i][j].newState(newStates);
                }
            }
            for (int i = 0; i < matrix.dim.first; ++i) {
                for (int j = 0; j < matrix.dim.second; ++j) {
                    matrix[i][j].setState(newStates[i][j]);
                }
            }
            if (t % 2 == 0)
                dumpMatrixToFile(t+1);
        }
    }
};


#endif //IMS_CELLULARAUTOMATON_H
