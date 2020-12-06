/**
 * @author1: Martin Haderka
 * @author2: Richard Klem
 * @email1: xhader00@stud.fit.vutbr.cz
 * @email2: xklemr00@stud.fit.vutbr.cz
 * @login1: xhader00
 * @login2: xklemr00
 * @date: 6.11.2020
 */
#ifndef IMS_CELL_H
#define IMS_CELL_H

#include "Matrix.h"
#include "Person.h"
#define NUM_OF_NEIGHBOURS 8

/**
 * @brief Enum struktura cellState přestavující stav buňky.
 * Může se jednat o zeď, o volnou buňkum kde nikdo není, nebo o obsazenou buňku, na které se nachází konkrétní osoba.
 */
enum cellState {
    WALL,
    FREE,
    OCCUPIED
};
/**
 * @brief Třída Cell přestavuje jendu buňku v prostoru - matici. Má stav typu cellState.
 * Velmi důležitým atributem je její stav a ukazatel na osobu, která buňku obývá.
 */
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

    unsigned int getY() {
        return y;
    }

    void setY(unsigned int newY) {
        Cell::y = newY;
    }

    explicit Cell(Matrix<Cell> * matrix) : parentMatrix{matrix}{}

    cellState getState() {
        return this->state;
    }
    void setState(cellState newState) {
        this->state = newState;
    }
    /**
     * @brief Metoda prozkoumá přilehlé okolí buňky a uloží ukazatele na až 8 sousedů buňky.
     */
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
