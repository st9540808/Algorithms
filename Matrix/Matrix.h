#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Matrix
{
	using size_type = typename std::vector<T>::size_type;
public:
	Matrix(size_type, size_type, const T& initval = T());
	~Matrix() = default;
	
	Matrix(const Matrix<T>&) = default;
	Matrix<T>& operator=(const Matrix<T>&) = default;

	Matrix(Matrix<T>&&) = default;
	Matrix<T>& operator=(Matrix<T>&&) = default;

	template <typename U>
	friend std::ostream& operator<<(std::ostream&, Matrix<U>&);
	template <typename U>
	friend std::istream& operator>>(std::istream&, Matrix<U>&);

	Matrix<T> operator+(const Matrix<T>& rhs) const;

private:
	size_type rows;
	size_type cols;
	std::vector<T> data;

	inline size_type index(size_type, size_type) const;
	inline typename std::vector<T>::iterator index_iter(size_type, size_type);
};

template <typename T>
Matrix<T>::Matrix(size_type inputrows, size_type inputcols, const T& initval)
	: rows(inputrows)
	, cols(inputcols)
	, data(rows * cols, initval)
{}

template <typename U>
std::ostream& operator<<(std::ostream& os, Matrix<U>& matrix)
{
	for (typename Matrix<U>::size_type i = 0; i < matrix.rows; ++i) {
		for (typename Matrix<U>::size_type j = 0; j < matrix.cols; ++j)
			os << std::setw(3) << *matrix.index_iter(i, j), os << " ";
		os << std::endl;
	}
	return os;
}

template <typename U>
std::istream& operator>>(std::istream& is, Matrix<U>& matrix)
{
	for (typename Matrix<U>::size_type i = 0; i < matrix.rows; ++i)
		for (typename Matrix<U>::size_type j = 0; j < matrix.cols; ++j)
			is >> matrix.data[matrix.index(i, j)];
	return is;
}

template <typename T>
typename Matrix<T>::size_type Matrix<T>::index(size_type row, size_type col) const
{
	return row * this->cols + col >= 0
		 ? row * this->cols + col
	     : throw std::out_of_range("index out of range");
}

template <typename T>
inline typename std::vector<T>::iterator
Matrix<T>::index_iter(size_type row, size_type col)
{
	return this->data.begin() + this->index(row, col);
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const
{
	if (this->rows != rhs.rows || this->cols != rhs.cols)
		throw std::out_of_range("wrong dimension in operator+");

	Matrix<T> result(this->rows, this->cols);
	for (auto resultIter = result.data.begin(), thisIter = this->data.begin(),
	          rhsIter = rhs.data.begin(); resultIter != result.data.end();
	        ++resultIter, ++thisIter, ++rhsIter)
		*resultIter = *thisIter + *rhsIter;

	return result;
}

#endif
