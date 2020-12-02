//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_MATRIX_H
#define IMS_MATRIX_H

#include <vector>
#include "Cell.h"

using namespace std;
class Matrix {
private:
    vector<vector<Cell> >m;
public:
    unsigned int size;
    Matrix(unsigned int x, unsigned int y): size{x * y} {
        m.resize(x, vector<Cell>(y, Cell()));
    }
    class MatrixRow {
    private:
        vector<Cell>& row;
    public:
        explicit MatrixRow(vector<Cell>& r) : row(r) {
        }
        Cell& operator[](unsigned int y) {
            return row.at(y);
        }
    };
    MatrixRow operator[](unsigned int x) {
        return MatrixRow(m.at(x));
    }
};

#endif //IMS_MATRIX_H
