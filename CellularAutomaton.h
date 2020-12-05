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
#include <cmath>
#include "Matrix.h"
#include "Cell.h"
#include "Person.h"


class CellularAutomaton {
private:
    Matrix<Cell> * matrix;
    vector<Person> persons;
    unsigned int x = 0;
    unsigned int y = 0;
    vector<pair<unsigned int, unsigned int>> walls;

public:
    Matrix<Cell> &getMatrix() {
        return *matrix;
    }

    void setMatrix(Matrix<Cell> &m) {
        CellularAutomaton::matrix = &m;
    }
    unsigned int getX() {
        return x;
    }

    void setX(unsigned int newX) {
        CellularAutomaton::x = newX;
    }

    unsigned int getY() {
        return y;
    }

    void setY(unsigned int newY) {
        CellularAutomaton::y = newY;
    }

    void initInfection(const unsigned int infectionRatio, const unsigned int immuneRatio) {
        srand((int) time(nullptr)); // Set random seed
        unsigned int infectedCount = round((double) persons.size() / infectionRatio);
        unsigned int immuneCount = round((double) persons.size() / immuneRatio);
        if (infectedCount == 0)
            infectedCount = 1;
        if (immuneCount == 0)
            immuneCount = 1;

        printf("Infecting randomly: %d persons\n", infectedCount);
        for (unsigned int i = 0; i < infectedCount; ++i) {
            //auto index = rand() % persons.size();  // Případ, kdy rand() vygeneruje stejné číslo se neřeší
            persons.at(i).setState(INFECTED);
            persons.at(i).setNextState(INFECTED);
        }
        printf("Immuning randomly: %d persons\n", immuneCount);
        for (unsigned int i = 0; i < immuneCount; ++i) {
            persons.at(i).setState(IMMUNE);
            persons.at(i).setNextState(IMMUNE);
        }
    }

    void initWalls(Matrix<Cell> * cellMatrix) {
        for (const auto & wall : walls) {
            (*cellMatrix)[wall.first][wall.second].setState(WALL);
        }
    }

    CellularAutomaton(unsigned int x, unsigned int y, unsigned int numOfPersons, const vector<pair<unsigned int, unsigned int>> * walls):
        matrix{new Matrix<Cell>(x, y)},
        persons{vector<Person>(numOfPersons, Person())},
        x{x},
        y{y},
        walls{*walls}
        {;    };

    void dumpMatrixToFile(unsigned int time) {
        string fileName = "matrix_dump" + to_string(time) + ".txt";
        ofstream file(fileName);
        for (unsigned int i = 0; i < getX(); ++i) {
            for (unsigned int j = 0; j < getY(); ++j) {
                auto person = (*matrix)[i][j].getPerson();
                if (person != nullptr){
                    file << person->getState();
                }
                else
                    file << (*matrix)[i][j].getState();
            }
            file << endl;
        }
        file.close();
    }

    void initPersonPositions() {
        srand((int) time(nullptr)); // Set random seed
        for (auto & person: persons) {
            auto newPersonX = rand() % getX();
            auto newPersonY = rand() % getY();
            if ((*matrix)[newPersonX][newPersonY].getState() != FREE) {
                bool found = false;
                for (unsigned int i = 0; i < getX(); ++i) {
                    for (unsigned int j = 0; j < getY(); ++j) {
                        if ((*matrix)[i][j].getState() == FREE) {
                            (*matrix)[i][j].setState(OCCUPIED);
                            (*matrix)[i][j].setPerson(&person);
                            person.setX(i);
                            person.setY(j);
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
            }
            else {
                (*matrix)[newPersonX][newPersonY].setState(OCCUPIED);
                (*matrix)[newPersonX][newPersonY].setPerson(&person);
                person.setX(newPersonX);
                person.setY(newPersonY);
            }
        }
    }

    /**
     * Inicalizuje atributy bunek
     */
    void initCellPositions() {
        for (unsigned int i = 0; i < getX(); ++i) {
            for (unsigned int j = 0; j < getY(); ++j) {
                (*matrix)[i][j].setX(i);
                (*matrix)[i][j].setY(j);
                (*matrix)[i][j].initNeighbours();
            }
        }
    }

    bool nextState(Matrix<Cell> * oldMatrix, Matrix<Cell> * newMatrix) {
        bool allInfected = true;
        for (auto & person: persons) {
            for (unsigned int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
                auto neighbour = (*oldMatrix)[person.getX()][person.getY()].getNeighbours()[i];
                if (neighbour != nullptr && neighbour->getPerson() != nullptr && neighbour->getPerson()->getState() == INFECTED)
                    person.setNextState(INFECTED);
            }
            (*newMatrix)[person.getX()][person.getY()].setPerson(&person);
            (*newMatrix)[person.getX()][person.getY()].setState(OCCUPIED);

            if (person.getState() == HEALTHY)
                allInfected = false;
        }
        // Aktualizuji se stavy lidi, ale az po te co si vsichni vypocitaji novy stav z aktualnich hodnot.
        for (auto & person: persons)
            person.setState(person.getNextState());

        return allInfected;
    }

    void simulate(const unsigned int time, const unsigned int infectionRatio, unsigned int immuneRatio, const unsigned int step) {
        initInfection(infectionRatio, immuneRatio);
        dumpMatrixToFile(0);
        // Cyklí se přes modelový čas!
        for (unsigned int t = 0; t < time; ++t) {
            static bool allInfected = false;
            auto newMatrix = new Matrix<Cell>(getX(), getY());
            initCellPositions();
            initWalls(newMatrix);
            allInfected |= nextState(&getMatrix(), newMatrix);

            matrix = newMatrix;

            if (t % step == 0) {
                dumpMatrixToFile(t+1);
            }
            else if ((t % step != 0) && (allInfected)){
                dumpMatrixToFile(t+1);
                return;
            }
            if (allInfected)
                return;
        }
    }
};


#endif //IMS_CELLULARAUTOMATON_H
