#include "Matrix.h"

template<typename T>
Matrix<T>::Matrix(int rownum, int colnum)
	:m_rowsize(rownum), m_colsize(colnum), m_size(rownum * colnum)
{
	m_matrix.resize(rownum);

	for (int i = 0; i < m_matrix.size(); i++)
	{
		m_matrix[i].resize(m_colsize, 0);
	}
}

template<typename T>
void Matrix<T>::MatrixEdit(int rownum, int colnum, T value)
{
	m_matrix[rownum][colnum] = value;
}

template<typename T>
std::vector<T> Matrix<T>::GetRow(int row)
{
	return m_matrix[row];
}

template<typename T>
std::vector<T> Matrix<T>::GetCol(int col)
{
	std::vector<T>column;
	
	for (int i = 0; i < m_rowsize; i++)
	{
		column.push_back(m_matrix[i][col]);
	}
	return col;
}

template<typename T>
std::vector<std::vector<T>> Matrix<T>::GetMat()
{
	return m_matrix;
}

template<typename T>
int Matrix<T>::GetSize()
{
	return m_size;
}

template<typename T>
void Matrix<T>::PrintMat()
{
	for (int i = 0; i < m_rowsize; i++)
	{
		for (int x = 0; x < m_colsize; x++)
		{
			std::cout << m_matrix[i][x] << " ";
		}
		
		std::cout << std::endl;
	}
	std::cout << std::endl;
}