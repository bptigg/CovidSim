#pragma once

#include <vector>

#include "Logging API.h"

template<typename T>
class Matrix
{
private:
	unsigned int m_rowsize;
	unsigned int m_colsize;
	unsigned int m_size;
	std::vector < std::vector<T> > m_matrix;

public:
	Matrix(int rownum, int colnum);
	void MatrixEdit(int rownum, int colnum, T value);

	std::vector<T> GetRow(int row);
	std::vector<T> GetCol(int col);
	int GetSize();

	std::vector < std::vector<T> > GetMat();
	void PrintMat();

	
};
