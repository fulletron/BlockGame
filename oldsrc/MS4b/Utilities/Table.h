#ifndef __TABLE_H_
#define __TABLE_H_

/*
#include <cassert>
#include <vector>
#include "..\..\Game\definitions.h"

#define _UtilitiesNSTable GS::UtilitiesNS::Table

namespace GS {
namespace UtilitiesNS{

template <typename T>
class Table
{
public:
	Table()
		: m_rows(0), m_cols(0)
	{}
	Table(_UINT32 a_rows, _UINT32 a_cols)
		: m_rows(a_rows), m_cols(a_cols), m_matrix(a_rows*a_cols)
	{}
	Table(_UINT32 a_rows, _UINT32 a_cols, const T & a_value)
		: m_rows(a_rows), m_cols(a_cols), m_matrix(a_rows*a_cols, a_value)
	{}

	T & getDataAt(_UINT32 a_row, _UINT32 a_col)
	{
		return m_matrix[a_row * m_cols + a_col];
	}

	const T & getDataAt(_UINT32 a_row, _UINT32 a_col) const
	{
		return m_matrix[a_row * m_cols + a_col];
	}

	typedef typename std::vector<T>::iterator iter;
	typedef typename std::vector<T>::const_iterator c_iter;

	iter begin(){	return m_matrix.begin();	}
	iter end()	{	return m_matrix.end();		}

	c_iter begin() const{	return m_matrix.begin();	}
	c_iter end() const	{	return m_matrix.end();		}

	_UINT32 numRows() const {return m_rows;}
	_UINT32 numCols() const {return m_cols;}

	void resize(_UINT32 a_rows, _UINT32 a_cols)
	{
		m_rows = a_rows;
		m_cols = a_cols;
		m_matrix.resize(a_rows * a_cols);
	}

	void resize(_UINT32 a_rows, _UINT32 a_cols, const T & a_value)
	{
		m_rows = a_rows;
		m_cols = a_cols;
		m_matrix.resize(a_rows * a_cols, a_value);
	}

private:
	_UINT32					m_rows;
	_UINT32					m_cols;
	std::vector<T>			m_matrix;
};

};
};
*/
#endif