#pragma once

#include <vector>
#include <ostream>

#include "Logging API.h"

//#include "Scenario.h"

template<typename T>
class Matrix
{
private:
	unsigned int m_rowsize;
	unsigned int m_colsize;
	unsigned int m_size;
	std::vector < std::vector<T> > m_matrix;

public:
	Matrix(int rownum, int colnum)
		: m_rowsize(rownum), m_colsize(colnum), m_size(rownum* colnum)
	{
		m_matrix.resize(rownum);

		for (int i = 0; i < m_matrix.size(); i++)
		{
			m_matrix[i].resize(m_colsize, 0);
		}
	}
	
	void MatrixEdit(int rownum, int colnum, T value)
	{
		m_matrix[rownum - 1][colnum - 1] = value;
	}


	std::vector<T> GetRow(int row)
	{
		return m_matrix[row - 1];
	}

	std::vector<T> GetCol(int col)
	{
		std::vector<T>column;

		for (unsigned int i = 0; i < m_rowsize; i++)
		{
			column.push_back(m_matrix[i][col - 1]);
		}
		return column;
	}

	int GetSize()
	{
		return m_size;
	}

	std::vector < std::vector<T> > GetMat()
	{
		return m_matrix;
	}

	void PrintMat()
	{
		for (unsigned int i = 0; i < m_rowsize; i++)
		{
			for (unsigned int x = 0; x < m_colsize; x++)
			{
				std::cout << m_matrix[i][x] << " ";
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void PrintMat(std::ostream &Scenariofile)
	{
		for (unsigned int i = 0; i < m_rowsize; i++)
		{
			for (unsigned int x = 0; x < m_colsize; x++)
			{
				Scenariofile << m_matrix[i][x] << " ";
			}

			Scenariofile << std::endl;
		}
		Scenariofile << std::endl;
	}

	
};
