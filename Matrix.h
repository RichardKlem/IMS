/**
 * @author1: Martin Haderka
 * @author2: Richard Klem
 * @email1: xhader00@stud.fit.vutbr.cz
 * @email2: xklemr00@stud.fit.vutbr.cz
 * @login1: xhader00
 * @login2: xklemr00
 * @date: 6.11.2020
 */
#ifndef IMS_MATRIX_H
#define IMS_MATRIX_H

#include <vector>

using namespace std;
/**
 * @brief Třída Matrix reprezentuje prostor simulace. Implementuje operátory [] pro přirozenější práci s maticí.
 * @tparam T Typ jakého jsou položky matice.
 */
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
