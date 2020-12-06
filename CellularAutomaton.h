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
#include <random>
#include <chrono>
#include "Matrix.h"
#include "Cell.h"
#include "Person.h"

inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

enum MOVE {
    FORWARD,
    RIGHT,
    BACK,
    LEFT,
    STAY
};

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
        //srand((int) time(nullptr)); // Set random seed
        unsigned int infectedCount = round((double) persons.size() / 100 * infectionRatio);
        unsigned int immuneCount = round((double) persons.size() / 100 * immuneRatio);
        if (infectedCount == 0)
            infectedCount = 1;
        if (immuneCount == 0)
            immuneCount = 1;

        int j = 0;
        for (unsigned int i = 0; i < infectedCount; ++i) {
            persons.at(j).setState(INFECTED);
            persons.at(j).setNextState(INFECTED);
            j++;
        }
        for (unsigned int i = 0; i < immuneCount; ++i) {
            persons.at(j).setState(IMMUNE);
            persons.at(j).setNextState(IMMUNE);
            j++;
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

    void dumpMatrixToFile(unsigned int time, const string * dumpDir) {
        string fileName = *dumpDir + separator() + "matrix_dump" + to_string(time) + ".txt";
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
    static void dumpCyclesToFile(const unsigned int cycles, const string * dumpDir) {
        string fileName = *dumpDir + separator() + "results.txt";
        ofstream file(fileName);
        file << cycles << endl;
        file.close();
    }

    void initPersonPositions() {
        for (auto & person: persons) {
            bool didNotFoundPosition = true;
            do {
                auto newPersonX = rand(0, getX() - 1);
                auto newPersonY = rand(0, getY() - 1);
                if ((*matrix)[newPersonX][newPersonY].getState() == FREE) {
                    (*matrix)[newPersonX][newPersonY].setState(OCCUPIED);
                    (*matrix)[newPersonX][newPersonY].setPerson(&person);
                    person.setX(newPersonX);
                    person.setY(newPersonY);
                    didNotFoundPosition = false;
                }
            } while (didNotFoundPosition);
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
    /**
     * @brief Metoda pocita a nastavuje novou pozici a novy stav cloveka. Clovek muze jit dopredu, dozadu, doleva,
     * doprava nebo muze stat na miste. V dany okamzik take muze zmenit svuj stav, pokud neni immunni a nekdo z jeho
     * okoli ho nakazi.
     * @param oldMatrix Stara mistnost
     * @param newMatrix Nova mistnost
     * @param forwardP Pravdepodobnost pohybu dopredu
     * @param rightP Pravdepodobnost pohybu doprava
     * @param leftP Pravdepodobnost pohybu doleva
     * @param backP Pravdepodobnost pohybu dozadu
     * @param stayP Pravdepodobnost zustanani na miste
     * @return Vraci true, kdyz jsou vsichni lide nakazeni nebo imunni, jinak false
     */
    bool nextState(Matrix<Cell> * oldMatrix,
                   Matrix<Cell> * newMatrix,
                   const unsigned int forwardP,
                   const unsigned int rightP,
                   const unsigned int leftP,
                   const unsigned int backP,
                   const unsigned int stayP) {
        bool allInfectedOrImmune = true;
        for (auto & person: persons) {
            for (unsigned int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
                auto neighbour = (*oldMatrix)[person.getX()][person.getY()].getNeighbours()[i];
                if (
                        neighbour != nullptr &&
                        neighbour->getPerson() != nullptr &&
                        neighbour->getPerson()->getState() == INFECTED &&
                        person.getState() != IMMUNE
                        )
                    person.setNextState(INFECTED);
            }
            //Vygeneruje kam jde.
            auto nextMoveKoef = rand(0, 100);
            MOVE nextMove;
            if ((nextMoveKoef > 0) && (nextMoveKoef < forwardP))
                nextMove = FORWARD;
            else if ((nextMoveKoef > forwardP) && (nextMoveKoef < forwardP + rightP))
                nextMove = RIGHT;
            else if ((nextMoveKoef > forwardP + rightP) && (nextMoveKoef < forwardP + rightP + backP))
                nextMove = BACK;
            else if ((nextMoveKoef > forwardP + rightP + backP) && (nextMoveKoef < forwardP + rightP + backP + leftP))
                nextMove = LEFT;
            else
                nextMove = STAY;

            //Kdyz je tam volno, tak se tam zapise, jinak zkusi dalsi moznost, prinejhorsim zustane na miste.
            switch (nextMove) {
                case FORWARD:
                    if (
                            (person.getX() != 0) &&
                            (*oldMatrix)[person.getX() - 1][person.getY()].getState() == FREE &&
                            (*newMatrix)[person.getX() - 1][person.getY()].getState() == FREE
                        )
                    {
                        (*newMatrix)[person.getX() - 1][person.getY()].setPerson(&person);
                        (*newMatrix)[person.getX() - 1][person.getY()].setState(OCCUPIED);
                        person.setX(person.getX() - 1);
                        break;
                    }
                case RIGHT:
                    if (
                            (person.getY() < (*oldMatrix).dim.second - 1) &&
                            (*oldMatrix)[person.getX()][person.getY() + 1].getState() == FREE &&
                            (*newMatrix)[person.getX()][person.getY() + 1].getState() == FREE
                        )
                    {
                        (*newMatrix)[person.getX()][person.getY() + 1].setPerson(&person);
                        (*newMatrix)[person.getX()][person.getY() + 1].setState(OCCUPIED);
                        person.setY(person.getY() + 1);
                        break;
                    }
                case BACK:
                    if (
                            (person.getX() < (*oldMatrix).dim.first - 1) &&
                            (*oldMatrix)[person.getX() + 1][person.getY()].getState() == FREE &&
                            (*newMatrix)[person.getX() + 1][person.getY()].getState() == FREE
                        )
                    {
                        (*newMatrix)[person.getX() + 1][person.getY()].setPerson(&person);
                        (*newMatrix)[person.getX() + 1][person.getY()].setState(OCCUPIED);
                        person.setX(person.getX() + 1);
                        break;
                    }
                case LEFT:
                        if (
                                (person.getY() != 0) &&
                                (*oldMatrix)[person.getX()][person.getY() - 1].getState() == FREE &&
                                (*newMatrix)[person.getX()][person.getY() - 1].getState() == FREE
                            )
                        {
                            (*newMatrix)[person.getX()][person.getY() - 1].setPerson(&person);
                            (*newMatrix)[person.getX()][person.getY() - 1].setState(OCCUPIED);
                            person.setY(person.getY() - 1);
                            break;
                        }
                default:
                    (*newMatrix)[person.getX()][person.getY()].setPerson(&person);
                    (*newMatrix)[person.getX()][person.getY()].setState(OCCUPIED);

            }

            if (person.getState() == HEALTHY)
                allInfectedOrImmune = false;
        }
        // Aktualizuji se stavy lidi, ale az po te co si vsichni vypocitaji novy stav z aktualnich hodnot.
        for (auto & person: persons)
            person.setState(person.getNextState());

        return allInfectedOrImmune;
    }

    static unsigned long rand(unsigned long a, unsigned long b) {
        typedef std::mt19937 rng_type;
        std::uniform_int_distribution<rng_type::result_type> udist(a, b);
        rng_type rng(chrono::steady_clock::now().time_since_epoch().count());
        rng_type::result_type random_number = udist(rng);
        return random_number;
    }
    void simulate(unsigned int time,
                  const unsigned int step,
                  const unsigned int infectionRatio,
                  unsigned int immuneRatio,
                  const unsigned int forwardP,
                  const unsigned int rightP,
                  const unsigned int leftP,
                  const unsigned int backP,
                  const unsigned int stayP,
                  const string *dumpDir) {
        initInfection(infectionRatio, immuneRatio);
        dumpMatrixToFile(0, dumpDir);
        // Cyklí se přes modelový čas!
        for (unsigned int t = 0; t < ++time; ++t) {
            static bool allInfectedOrImmune = false;
            auto newMatrix = new Matrix<Cell>(getX(), getY());
            initCellPositions();
            initWalls(newMatrix);
            allInfectedOrImmune |= nextState(&getMatrix(), newMatrix, forwardP, rightP, leftP, backP, stayP);

            matrix = newMatrix;

            if (t % step == 0) {
                dumpMatrixToFile(t+1, dumpDir);
            }
            else if ((t % step != 0) && (allInfectedOrImmune)){
                //cout << "Simulation got " << t << " cycles" << endl;
                dumpMatrixToFile(t+1, dumpDir);
                dumpCyclesToFile(t, dumpDir);
                return;
            }
            if (allInfectedOrImmune) {
                //cout << "Simulation got " << t << " cycles" << endl;
                dumpCyclesToFile(t, dumpDir);
                return;
            }
        }
    }
};


#endif //IMS_CELLULARAUTOMATON_H
