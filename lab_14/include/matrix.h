#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdint>

class MatrixException {
public:
	virtual const char * log() = 0;
};

class BadIndex : public MatrixException {
	const char * log() { return "ACCESS: bad index."; };
};

class BadAdd : public MatrixException {
	const char * log() { return "ADD: dimensions do not match."; };
};

class BadMul: public MatrixException {
	const char * log() { return "MUL: #arg1.columns != #arg2.rows."; };
};



class Matrix {
public:
	Matrix() : n_(0), m_(0), array_(NULL) { };
	Matrix(size_t n, size_t m) : 
		n_(n), 
		m_(m), 
		array_(allocate_matrix(n, m)) { };
	~Matrix();

	Matrix(const Matrix & other);
	Matrix & operator=(Matrix other);
	void swap(Matrix & other);
	const int32_t * operator[](std::size_t index) const;
	int32_t * operator[](std::size_t index);
	const int32_t & at(int index1, int index2) const;
	int32_t & at(int index1, int index2);
	
	Matrix operator*(const Matrix & other) const;
	Matrix operator+(const Matrix & other) const;

	Matrix & operator*=(const Matrix & other);
	Matrix & operator+=(const Matrix & other);

	friend std::ifstream & operator>>(std::ifstream & in, Matrix & matrix);
	friend std::ostream & operator<<(std::ostream & out, const Matrix & matrix);

private:
	static int32_t ** allocate_matrix(size_t n, size_t m);
	size_t n_, m_;
	int32_t ** array_;
};

std::ifstream & operator>>(std::ifstream & in, Matrix & matrix);
std::ostream & operator<<(std::ostream & out, const Matrix & matrix);
