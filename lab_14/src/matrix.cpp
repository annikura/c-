#include "matrix.h"

Matrix::~Matrix(){
	if (array_){
		delete [] array_[0];
		delete [] array_;
	}
}

Matrix::Matrix(const Matrix & other) : n_(other.n_), m_(other.m_) {
	if (n_ * m_ == 0)
		array_ = NULL;
	else{
		array_ = this->allocate_matrix(n_, m_);
		memcpy(array_[0], other.array_[0], n_ * m_ * sizeof(int32_t));
	}
}

Matrix & Matrix::operator=(Matrix other) {
	this->swap(other);
	return *this;
}

void Matrix::swap(Matrix & other){
	std::swap(array_, other.array_);
	std::swap(n_, other.n_);
	std::swap(m_, other.m_);
}

const int32_t & Matrix::at(int index1, int index2) const {
	if (index1 < 0 || index2 < 0 || 
		(std::size_t)index1 >= n_ || (std::size_t)index2 >= m_)
		throw BadIndex();
	return this->operator[](index1)[index2];
}

int32_t & Matrix::at(int index1, int index2) {
	if (index1 < 0 || index2 < 0 || 
		(std::size_t)index1 >= n_ || (std::size_t)index2 >= m_)
		throw BadIndex();
	return this->operator[](index1)[index2];
}

const int32_t * Matrix::operator[](std::size_t index) const {
	return array_[index];
}
int32_t * Matrix::operator[](std::size_t index) {
	return array_[index];
}

Matrix Matrix::operator*(const Matrix & other) const {
	if (m_ != other.n_)
		throw BadMul();
	Matrix result(n_, other.m_);

	for (std::size_t i = 0; i < n_; i++)
		for (std::size_t j = 0; j < other.m_; j++)
			for (std::size_t k = 0; k < m_; k++)
					result[i][j] += array_[i][k] * other[k][j];

	return result;
}

Matrix Matrix::operator+(const Matrix & other) const {
	if (n_ != other.n_ || m_ != other.m_)
		throw BadAdd();
	Matrix result(n_, m_);

	for (std::size_t i = 0; i < n_; i++)
		for (std::size_t j = 0; j < m_; j++)
			result[i][j] = array_[i][j] + other[i][j];
	
	return result;
}

Matrix & Matrix::operator*=(const Matrix & other) {
	*this = this->operator*(other);
	return *this; 
}

Matrix & Matrix::operator+=(const Matrix & other) {
	*this = this->operator+(other);
	return *this;
}

std::ifstream & operator>>(std::ifstream & in, Matrix & matrix){
	std::size_t n, m;
	in >> n >> m;
	Matrix mtrx_to_read(n, m);
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < m; j++)
			in >> mtrx_to_read[i][j];
	}
	matrix = mtrx_to_read;
	return in;
}

std::ostream & operator<<(std::ostream & out, const Matrix & matrix){
	for (size_t i = 0; i < matrix.n_; i++){
		for (size_t j = 0; j < matrix.m_; j++)
			out << matrix[i][j] << " ";
		out << std::endl;
	}
	return out;
}

int32_t ** Matrix::allocate_matrix(std::size_t n, std::size_t m){
	int32_t ** return_value = new int32_t*[n];
	int32_t * tmp = new int32_t[n * m];
	for (std::size_t i = 0; i < n; i++)
		return_value[i] = tmp + i * m;
	memset(return_value[0], 0, n * m * sizeof(int32_t));
	return return_value;
}
