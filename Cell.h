//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

#include "Matrix.h"
#include "Person.h"
#define NUM_OF_NEIGHBOURS 8

enum cellState {
    WALL,
    FREE,
    OCCUPIED
};
class Cell {
private:
    cellState state = FREE;
    Cell * neighbours [8] {nullptr};
    Person * person{nullptr};
    unsigned int x = 0, y = 0;
    Matrix<Cell> * parentMatrix;

public:
    Cell *const *getNeighbours() {
        return neighbours;
    }


    Person *getPerson() {
        return person;
    }

    void setPerson(Person *newPerson) {
        person = newPerson;
    }

    unsigned int getX() {
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

    Cell(Matrix<Cell> * matrix) : parentMatrix{matrix}{;}

    cellState getState() {
        return this->state;
    }
    void setState(cellState newState) {
        this->state = newState;
    }
    void initNeighbours(){
        if (x >= 1) {
            if (y >= 1)
                neighbours[0] = &(*parentMatrix)[x - 1][y - 1];
            neighbours[1] = &(*parentMatrix)[x - 1][y];
            if (y < parentMatrix->dim.second - 1)
                neighbours[2] = &(*parentMatrix)[x - 1][y + 1];
        }

        if (y >= 1)
            neighbours[3] = &(*parentMatrix)[x][y-1];
        if (y < parentMatrix->dim.second - 1)
            neighbours[4] = &(*parentMatrix)[x][y+1];

        if (x < parentMatrix->dim.first - 1) {
            if (y >= 1)
                neighbours[5] = &(*parentMatrix)[x + 1][y - 1];
            neighbours[6] = &(*parentMatrix)[x + 1][y];
            if (y < parentMatrix->dim.second - 1)
                neighbours[7] = &(*parentMatrix)[x + 1][y + 1];
        }
        for (auto & neighbour: neighbours) {
            if (neighbour != nullptr && neighbour->getState() == WALL)
                neighbour = nullptr;
        }
    }
};

#endif //IMS_CELL_H
