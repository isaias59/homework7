#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "array.hpp"
#include <iostream>
#include <stdexcept>

template <typename T>
class Matrix {
public:
    Matrix() : rows{ 0 }, cols{ 0 }, data{ Array<Array<T>>(0) } {
    }

    Matrix(int rows, int cols) : rows{ rows }, cols{ cols }, data{ Array<Array<T>>(rows) } {
        for (int i = 0; i < rows; ++i) {
            data[i] = Array<T>(cols);
        }
    }

    Array<T>& operator[](int row) {
        if (!in_bounds(row)) {
            throw std::out_of_range("Exception operator[](" + std::to_string(row) + ") Out Of Range");
        }
        return data[row];
    }

    const Array<T>& operator[](int row) const {
        if (!in_bounds(row)) {
            throw std::out_of_range("Exception operator[](" + std::to_string(row) + ") Out Of Range");
        }
        return data[row];
    }

    int num_rows() const {
        return rows;
    }

    int num_cols() const {
        return cols;
    }

    void fill(const T& val) {
        for (int i = 0; i < rows; ++i) {
            data[i].fill(val);
        }
    }

    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = fn(i, j);
            }
        }
    }

private:
    int rows, cols;
    Array<Array<T>> data;

    bool in_bounds(int index) const {
        return index >= 0 && index < rows;
    }
};


template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.num_rows(); ++i) {
        out << matrix[i] << '\n';
    }
    return out;
}


template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    for (int i = 0; i < matrix.num_rows(); ++i) {
        for (int j = 0; j < matrix.num_cols(); ++j) {
            in >> matrix[i][j];
        }
    }
    return in;
}

#endif

