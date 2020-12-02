//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

class Cell {
private:
    int state = 0;
    int numOfInfections = 0;
    bool immune = false;

public:
    int getNumOfInfections() {
        return numOfInfections;
    }

    void setNumOfInfections(int numOfInfections) {
        Cell::numOfInfections = numOfInfections;
    }

    bool isImmune() {
        return immune;
    }

    void setImmune(bool immune) {
        Cell::immune = immune;
    }

    int getState() {
        return this->state;
    }
    void setState(int newState) {
        this->state = newState;
    }
};

#endif //IMS_CELL_H
