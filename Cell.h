//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

#define NUM_OF_NEIGHBOURS 8

class Cell {
private:
    unsigned int state = 0;
    unsigned int numOfInfections = 0;
    bool immune = false;
    //Cell * neighbours [8];
    unsigned int x, y;
public:
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
    Cell(unsigned int x, unsigned int y): x{x}, y{y}{
        ;
    }
};

#endif //IMS_CELL_H
