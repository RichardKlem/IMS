//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELLULARAUTOMATON_H
#define IMS_CELLULARAUTOMATON_H

#include "Matrix.h"


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

    CellularAutomaton(unsigned int x, unsigned int y): matrix{Matrix(x, y)}{;
    };
};


#endif //IMS_CELLULARAUTOMATON_H
