#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <cstdio>
#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(Matrix const &m);
    ~Matrix();

    std::size_t get_rows() const;
    std::size_t get_cols() const;
    void set(std::size_t i, std::size_t j, int val);
    int get(std::size_t i, std::size_t j) const;
    void print(FILE *f) const;

    Matrix operator+(Matrix const &m) const;
    Matrix operator-(Matrix const &m) const;
    Matrix operator*(Matrix const &m) const;

    Matrix& operator=(Matrix const &m);

    void swap(Matrix &m);

    Matrix& operator+=(Matrix const &m);
    Matrix& operator-=(Matrix const &m);
    Matrix& operator*=(Matrix const &m);

    bool operator==(Matrix const &m) const;
    bool operator!=(Matrix const &m) const;

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};

#endif
