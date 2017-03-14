#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <vector>

template <typename T>
class Matrix
{
	using size_type = typename std::vector<T>::size_type;
private:
	size_type rows;
	size_type cols;
	std::vector<T> data;

public:
	Matrix(size_type, size_type, const T& initval = T());
	~Matrix() = default;
	
	Matrix(const Matrix<T>&) = default;
	Matrix<T>& operator=(const Matrix<T>&) = default;

	Matrix(Matrix<T>&&) = default;
	Matrix<T>& operator=(Matrix<T>&&) = default;

	template<typename U>
	friend std::ostream& operator<<(std::ostream&, Matrix<U>&&);
	template<typename U>
	friend std::istream& operator>>(std::istream&, Matrix<U>&);
};

template <typename T>
Matrix<T>::Matrix(size_type inputrows, size_type inputcols, const T& initval)
	: rows(inputrows)
	, cols(inputcols)
	, data(rows * cols, initval)
{}

template <typename U>
std::ostream& operator<<(std::ostream& os, Matrix<U>&& matrix)
{
	for (auto&& i : matrix.data)
		os << i << " ";
	return os;
}

template<typename U>
std::istream& operator>>(std::istream& is, Matrix<U>& matrix)
{
	for (typename Matrix<U>::size_type i = 0; i < matrix.rows; ++i)
		for (typename Matrix<U>::size_type j = 0; j < matrix.cols; ++j)
			is >> matrix.data[i * matrix.cols + j];
	return is;
}

#endif
