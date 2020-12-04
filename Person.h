//
// Created by rklem on 12/4/20.
//

#ifndef IMS_PERSON_H
#define IMS_PERSON_H

enum covidState {
        RESERVED1,
        RESERVED2,
        HEALTHY,
        INFECTED,
        IMMUNE,
        DEAD
};

class Person {
private:
    covidState state = HEALTHY;
    unsigned int numOfInfections = 0;
    unsigned int x = 0, y = 0;
public:
    covidState getState() {
        return state;
    }

    void setState(covidState state) {
        Person::state = state;
    }

    unsigned int getNumOfInfections() {
        return numOfInfections;
    }

    void setNumOfInfections(unsigned int numOfInfections) {
        Person::numOfInfections = numOfInfections;
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
