#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <cstring>
#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r, _cols = c;
    int *tmp = new int [r * c];
    _data = new int *[r];
    for (size_t i = 0; i < r; i++)
        _data[i] = tmp + i * c;

    memset(_data[0], 0, r * c * sizeof(int));
}

Matrix::~Matrix() {
    delete [] _data[0];
    delete [] _data;
}

Matrix::Matrix(Matrix const &m) {
    _rows = m._rows, _cols = m._cols;
    int *tmp = new int [_rows * _cols];
    _data = new int *[_rows];
    for (size_t i = 0; i < _rows; i++)
        _data[i] = tmp + i * _cols;

    memcpy(_data[0], m._data[0], _rows * _cols * sizeof(int));
}

std::size_t Matrix::get_rows() const{
    return _rows;
}
std::size_t Matrix::get_cols() const{
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    assert(i >= 0 && i < _rows && j >= 0 && j < _cols);
    _data[i][j] = val;
    return;
}

int Matrix::get(std::size_t i, std::size_t j) const{
    assert(i >= 0 && i < _rows && j >= 0 && j < _cols);
    return _data[i][j];
}

void Matrix::print(FILE* f) const{
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++)
            fprintf(f, "%d ", _data[i][j]);
        fprintf(f, "\n");
    }

}

bool Matrix::operator==(Matrix const &m) const{
    if (_rows != m._rows || _cols != m._cols)
        return false;
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            if (_data[i][j] != m._data[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(Matrix const &m) const{
    return !(this->operator==(m));
}

Matrix& Matrix::operator=(Matrix const &m){
    if (*this != m) {
        Matrix tmp(m);
        this->swap(tmp);
    }
    return *this;
}

Matrix& Matrix::operator+=(Matrix const &m) {
    assert(m._rows == _rows && m._cols == _cols);
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            _data[i][j] += m._data[i][j];
    return *this;
}

Matrix& Matrix::operator-=(Matrix const &m) {
    assert(m._rows == _rows && m._cols == _cols);
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            _data[i][j] -= m._data[i][j];
    return *this;
}

Matrix& Matrix::operator*=(Matrix const &m) {
    assert(m._rows == _cols);
    Matrix ret(_rows, m._cols);
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            for (size_t k = 0; k < m._cols; k++)
                ret._data[i][k] += _data[i][j] * m._data[j][k];

    this->swap(ret);

    return *this;
}

Matrix Matrix::operator+(Matrix const &m) const{
    Matrix ret(*this);
    ret.operator+=(m);
    return ret;
}

Matrix Matrix::operator-(Matrix const &m) const{
    Matrix ret(*this);
    ret.operator-=(m);
    return ret;
}

Matrix Matrix::operator*(Matrix const &m) const{
    Matrix ret(*this);
    ret.operator*=(m);
    return ret;
}


void Matrix::swap(Matrix &m){
    std::swap(m._data, _data);
    std::swap(m._cols, _cols);
    std::swap(m._rows, _rows);
    return;
}
