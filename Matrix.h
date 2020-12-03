//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_MATRIX_H
#define IMS_MATRIX_H

#include <vector>

using namespace std;
template  <class T> class Matrix {
private:
    vector<vector<T> >m;
public:
    unsigned int size;
    pair<unsigned int, unsigned int> dim;
    Matrix(unsigned int x, unsigned int y): size{x * y}, dim{x, y}{
        m.resize(x, vector<T>(y, T(this)));
    }
    class MatrixRow {
    private:
        vector<T>& row;
    public:
        explicit MatrixRow(vector<T>& r) : row(r) {
        }
        T& operator[](unsigned int y) {
            return row.at(y);
        }
    };
    MatrixRow operator[](unsigned int x) {
        return MatrixRow(m.at(x));
    }
};

#endif //IMS_MATRIX_H
