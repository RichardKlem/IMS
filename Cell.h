//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

#include "Matrix.h"
#define NUM_OF_NEIGHBOURS 8

class Cell {
private:
    unsigned int state = 0;
    unsigned int numOfInfections = 0;
    bool immune = false;
    Cell * neighbours [8] {nullptr};
    unsigned int x = 0, y = 0;
    Matrix<Cell> * parentMatrix;
public:
    unsigned int getX() const {
        return x;
    }

    void setX(unsigned int newX) {
        Cell::x = newX;
    }

    unsigned int getY() const {
        return y;
    }

    void setY(unsigned int newY) {
        Cell::y = newY;
    }

public:
    Cell(Matrix<Cell> * matrix) : parentMatrix{matrix}{;}

    unsigned int getNumOfInfections() {
        return numOfInfections;
    }

    void setNumOfInfections(unsigned int numOfInfections) {
        Cell::numOfInfections = numOfInfections;
    }

    bool isImmune() {
        return immune;
    }

    void setImmune(bool immune) {
        Cell::immune = immune;
    }

    unsigned int getState() {
        return this->state;
    }
    void setState(unsigned int newState) {
        this->state = newState;
    }
    void initNeighbours(){

        if (x - 1 >= 0) {
            if (y - 1 >= 0)
                neighbours[0] = &(*parentMatrix)[x - 1][y - 1];
            neighbours[1] = &(*parentMatrix)[x - 1][y];
            if (y + 1 < parentMatrix->dim.second)
                neighbours[2] = &(*parentMatrix)[x - 1][y + 1];
        }

        if (y - 1 >= 0)
            neighbours[3] = &(*parentMatrix)[x][y-1];
        if (y + 1 < parentMatrix->dim.second)
            neighbours[4] = &(*parentMatrix)[x][y+1];

        if (x + 1 < parentMatrix->dim.first) {
            if (y - 1 >= 0)
                neighbours[5] = &(*parentMatrix)[x + 1][y - 1];
            neighbours[6] = &(*parentMatrix)[x + 1][y];
            if (y + 1 < parentMatrix->dim.second)
                neighbours[7] = &(*parentMatrix)[x + 1][y + 1];
        }
    }
};

#endif //IMS_CELL_H
