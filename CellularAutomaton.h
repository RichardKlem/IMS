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
//#include <ctime>
#include <string>
#include <cmath>
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
        {};
    ~CellularAutomaton(){
        delete matrix;
    }
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
                auto newPersonX = randIMS(0, getX() - 1);
                auto newPersonY = randIMS(0, getY() - 1);
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
                   [[maybe_unused]] const unsigned int stayP,
                   bool model2) {
        bool allInfectedOrImmune = true;
        for (auto & person: persons) {
            for (unsigned int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
                auto neighbour = (*oldMatrix)[person.getX()][person.getY()].getNeighbours()[i];
                if (
                        neighbour != nullptr &&
                        neighbour->getPerson() != nullptr &&
                        person.getState() == HEALTHY
                        ) {
                    auto isAt = pair<unsigned int, unsigned int>{person.getX(), person.getY()};
                    pair<unsigned int, unsigned int> looingAt;
                    int isOk = neighbour->getPerson()->lookingAtCell(&looingAt);
                    if (neighbour->getPerson()->getState() == INFECTED) {
                        // Model 1 uvažuje pouze možnost nákazy napřímo. Dva lidé se dívají přímo na sebe.
                        if (isOk && looingAt == isAt)
                            person.setNextState(INFECTED);
                        // Model 2 přidává možnost nákazy z okolí
                        else if (isOk and model2){
                            auto gotInfection = randIMS(0,1000);
                            if (gotInfection < 100)
                                person.setNextState(INFECTED);
                        }
                    }
                }
            }
            // Vygeneruje se směr, kam člověk půjde.
            auto nextMoveKoef = randIMS(0, 100);
            direction nextMove;
            if (nextMoveKoef < forwardP)
                nextMove = FORWARD;
            else if ((nextMoveKoef >= forwardP) && (nextMoveKoef < forwardP + rightP))
                nextMove = RIGHT;
            else if ((nextMoveKoef >= forwardP + rightP) && (nextMoveKoef < forwardP + rightP + backP))
                nextMove = BACK;
            else if ((nextMoveKoef >= forwardP + rightP + backP) && (nextMoveKoef < forwardP + rightP + backP + leftP))
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
                    [[fallthrough]];
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
                    [[fallthrough]];
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
                    [[fallthrough]];
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
                    [[fallthrough]];
                default:
                    (*newMatrix)[person.getX()][person.getY()].setPerson(&person);
                    (*newMatrix)[person.getX()][person.getY()].setState(OCCUPIED);
            }
            if (nextMove != STAY)
                person.setLookDir(nextMove);
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
     * @brief Metoda obstarava samotnou simulaci sireni koronoaviru se zadanymi parametry.
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
    void simulate(const unsigned int step,
                  const unsigned int infectionRatio,
                  unsigned int immuneRatio,
                  const unsigned int forwardP,
                  const unsigned int rightP,
                  const unsigned int leftP,
                  const unsigned int backP,
                  const unsigned int stayP,
                  const string *dumpDir,
                  const bool model2) {
        initInfection(infectionRatio, immuneRatio);
        dumpMatrixToFile(0, dumpDir);
        unsigned int tp1 = 1;
        // Cyklí se přes modelový čas!
        static bool allInfectedOrImmune = false;
        for (unsigned int t = 0; t < ++tp1; ++t) {
            auto newMatrix = new Matrix<Cell>(getX(), getY());
            initCellPositions();
            initWalls(newMatrix);
            allInfectedOrImmune |= nextState(&getMatrix(), newMatrix, forwardP, rightP, leftP, backP, stayP, model2);

            auto matrixToDelete = matrix;
            matrix = newMatrix;
            delete matrixToDelete;
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
