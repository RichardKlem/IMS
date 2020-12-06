/**
 * @author1: Martin Haderka
 * @author2: Richard Klem
 * @email1: xhader00@stud.fit.vutbr.cz
 * @email2: xklemr00@stud.fit.vutbr.cz
 * @login1: xhader00
 * @login2: xklemr00
 * @date: 6.11.2020
 */
#ifndef IMS_PERSON_H
#define IMS_PERSON_H
#include "utils.h"

/**
 * @brief Enum struktura covidState představuje infekční stav člověka.
 * První dvě hodnoty jsou rezervovány pro snazší vizualizaci (ve vizualizaci se mixují stavy buněk se stavy lidí).
 * Člověk může být zdravý, nemocný/nakažený, nebo imunní. (Mrtvý je pro možné další rozšíření modelu.)
 */
enum covidState {
        RESERVED0,
        RESERVED1,
        HEALTHY,
        INFECTED,
        IMMUNE,
        DEAD
};

/**
 * @brief Třída Person představuje jednoho člověka v prostoru - matici.
 */
class Person {
private:
    covidState state = HEALTHY;
    covidState nextState = state;
    direction lookDir = static_cast<direction>(randIMS(FORWARD, LEFT));
    direction nextLookDir = lookDir;
    unsigned int x = 0, y = 0;
public:
    /**
     * @brief Funkce nastaví parametr lookingAt na
     * @param lookingAt
     * @return
     */
    int lookingAtCell(pair<unsigned int, unsigned int > * lookingAt) {
        pair<unsigned int, unsigned int> tmpPair;
        if (getLookDir() == FORWARD)
            tmpPair = {getX() - 1, getY()};
        else if (getLookDir() == RIGHT)
            tmpPair = {getX(), getY() + 1};
        else if (getLookDir() == BACK)
            tmpPair = {getX() + 1, getY()};
        else if (getLookDir() == LEFT)
            tmpPair = {getX(), getY() - 1};
        else {
            return 0;
        }
        *lookingAt = tmpPair;
        return 1;
    }

    covidState getState() {
        return state;
    }

    void setState(covidState newState) {
        Person::state = newState;
    }
    covidState getNextState() {
        return nextState;
    }

    void setNextState(covidState newNextState) {
        Person::nextState = newNextState;
    }
    direction getLookDir() {
        return lookDir;
    }

    void setLookDir(direction newLookDir) {
        Person::lookDir = newLookDir;
    }
    direction getNextLookDir() {
        return nextLookDir;
    }

    void setNextLookDir(direction newNextLookDir) {
        Person::nextLookDir = newNextLookDir;
    }

    unsigned int getX() {
        return x;
    }

    void setX(unsigned int newX) {
        Person::x = newX;
    }

    unsigned int getY() {
        return y;
    }

    void setY(unsigned int newY) {
        Person::y = newY;
    }
};

#endif //IMS_PERSON_H
