/**
 * @author1: Martin Haderka
 * @author2: Richard Klem
 * @email1: xhader00@stud.fit.vutbr.cz
 * @email2: xklemr00@stud.fit.vutbr.cz
 * @login1: xhader00
 * @login2: xklemr00
 * @date: 6.11.2020
 */
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

// Oddělovač nového řádku podle OS.
inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

/**
 * @brief Enum struktura personMove představuje směry, kam se může člověk vydat v dalším kroku.
 */
enum personMove {
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

    /**
     * @brief Inicializuje prvotní infekci podle zadaných parametrů.
     * Vektor lidí se prochází sekvenčně, protože pozice lidí je generovaná náhodně(pseudo) a proto je zaručeno,
     * že i infekce a imunita bude rozdělena dostatečně náhodně v prostoru.
     * @param infectionRatio Počet nakažených lidí v prostoru, v procentech (%).
     * @param immuneRatio Počet imunních lidí v prostoru, v procentech (%).
     */
    void initInfection(const unsigned int infectionRatio, const unsigned int immuneRatio) {
        unsigned int infectedCount = round((double) persons.size() / 100 * infectionRatio);
        unsigned int immuneCount = round((double) persons.size() / 100 * immuneRatio);
        if (infectedCount == 0)
            infectedCount = 1;
        if (immuneCount == 0)
            immuneCount = 1;

        // Vektor lidí se prochází sekvenčně, protože pozice lidí je generovaná náhodně(pseudo) a proto je zaručeno,
        // že i infekce a imunita bude rozdělena dostatečně náhodně v prostoru.
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
    /**
     * @brief Inicializuje stěny podobně jako to dělá konstruktor při vytváření nového CellularAutomaton objektu.
     * Tato metoda slouží pro inicializaci stěn v nové matici, která se tvoří každou iteraci simulace. Viz metoda
     * simulate této třídy.
     * @param cellMatrix Ukazatel na novou matici.
     */
    void initWalls(Matrix<Cell> * cellMatrix) {
        for (const auto & wall : walls) {
            (*cellMatrix)[wall.first][wall.second].setState(WALL);
        }
    }
    /**
     * @brief Konstruktor třídy CellularAutomaton, který nastaví atributy instance podle parametrů.
     * @param x Počet řádků matice reprezuntující modelovaný prostor.
     * @param y Počet sloupců matice reprezuntující modelovaný prostor.
     * @param numOfPersons Počet lidí v prostoru.
     * @param walls Vektor dvojic čísel reprezentujících souřadnice jednotlivých bloků zdí/překážek v prostoru.
     */
    CellularAutomaton(unsigned int x, unsigned int y, unsigned int numOfPersons, const vector<pair<unsigned int, unsigned int>> * walls):
        matrix{new Matrix<Cell>(x, y)},
        persons{vector<Person>(numOfPersons, Person())},
        x{x},
        y{y},
        walls{*walls}
        {;    };
    /**
     * @brief Uloží data do souboru s názvem podle modelového času.
     * @param time Hodnota modelového času.
     * @param dumpDir Název složky, kam se soubor s daty uloží.
     */
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
    /**
     * @brief Uloží hodnotu počtu cyklů simulace do souboru.
     * @param cycles Počet cyklů simulace
     * @param dumpDir Název složky, kam se soubor s hodnotou uloží.
     */
    static void dumpCyclesToFile(const unsigned int cycles, const string * dumpDir) {
        string fileName = *dumpDir + separator() + "results.txt";
        ofstream file(fileName);
        file << cycles << endl;
        file.close();
    }
    /**
     * @brief Inicalizuje atributy lidí v prostoru (matici) včetně zapsání se do náhodně vybrané buňky.
     * Když je vybraná buňka obsazená, hledá se nová, dokud se nenajde volné místo.
     */
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
     * @brief Inicalizuje atributy bunek matice včetně zjištění sousedů.
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
     * @brief Metoda počítá a nastavuje novou pozici a nový stav člověka. Člověk může jít dopředu, dozadu, doleva,
     * doprava nebo může stát na míste. V daný okamžik také může změnit svůj stav, pokud není immunní a někdo z jeho
     * okolí ho nakazí.
     * @param oldMatrix Starý prostor.
     * @param newMatrix Nový prostor.
     * @param forwardP Pravděpodobnost pohybu dopředu.
     * @param rightP Pravděpodobnost pohybu doprava.
     * @param leftP Pravděpodobnost pohybu doleva.
     * @param backP Pravděpodobnost pohybu dozadu.
     * @param stayP Pravděpodobnost zůstání na místě.
     * @return Vrací true, když jsou všichni lidé nakažení nebo imunní, jinak false.
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
            // Vygeneruje se směr, kam člověk půjde.
            auto nextMoveKoef = rand(0, 100);
            personMove nextMove;
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

            // Kdyz je na cílené buňce volno, tak se tam osoba zapíše, jinak osoba zkusí další možnost,
            // "přinejhorším" zůstane stát.
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
            // Každá osoba, která je ještě zdravá, dá o sobě vědět.
            if (person.getState() == HEALTHY)
                allInfectedOrImmune = false;
        }
        // Aktualizují se stavy všech osob, ale až po té, co si všichni vypočítají nový stav z aktualních hodnot.
        // Jinak by se mohli osoby "srazit" na stejné buňce.
        for (auto & person: persons)
            person.setState(person.getNextState());
        // Navrátí se informace, jestli je ještě někdo zdravý nebo jsou už všichni nakažení.
        return allInfectedOrImmune;
    }

    /**
     * @brief Funkce vrací pseudo-náhodné číslo ze zadaného intervalu podle algoritmu
     * @param a leva mez intervalu
     * @param b prava mez intervalu
     * @return pseudo-nahodne cislo ze zadaneho intervalu
     */
    static unsigned long rand(unsigned long a, unsigned long b) {
        typedef std::mt19937 rng_type;
        std::uniform_int_distribution<rng_type::result_type> udist(a, b);
        rng_type rng(chrono::steady_clock::now().time_since_epoch().count());
        rng_type::result_type random_number = udist(rng);
        return random_number;
    }

    /**
     * @brief Metoda obstarava samotnou simulaci sireni koronoaviru se zadanymi parametry.
     * @param time
     * @param step Krok, se kterým se budou ukládat data z matice do souborů.
     * @param infectionRatio Počet nakažených lidí v prostoru, v procentech (%).
     * @param immuneRatio Počet imunních lidí v prostoru, v procentech (%).
     * @param forwardP Pravděpodobnost pohybu dopředu.
     * @param rightP Pravděpodobnost pohybu doprava.
     * @param leftP Pravděpodobnost pohybu doleva.
     * @param backP Pravděpodobnost pohybu dozadu.
     * @param stayP Pravděpodobnost zůstání na místě.
     * @param dumpDir Název složky, kam se budou ukládat data z prostoru (matice).
     */
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
                dumpMatrixToFile(t+1, dumpDir);
                dumpCyclesToFile(t, dumpDir);
                return;
            }
            // Pokud už v prostoru není žádný zdravý člověk, tak simulace končí.
            if (allInfectedOrImmune) {
                // Poslední výpis dat, kde jsou už všichni lidé nakažení. Přímé dokročení na konci simualce nehledě
                // na zadaný krok vypisování dat.
                dumpCyclesToFile(t, dumpDir);
                return;
            }
        }
    }
};


#endif //IMS_CELLULARAUTOMATON_H
