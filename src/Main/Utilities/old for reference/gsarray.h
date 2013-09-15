#ifndef __GSARRAY_H_
#define __GSARRAY_H_

#include "typedefinitions.h"

namespace GS {
namespace UtilitiesNS {

template<typename DATA_TYPE>
class GSArray
{
protected:
	DATA_TYPE* 			m_data;
	_UINT32				m_allocated;

public:
	inline DATA_TYPE & get(const _UINT32 & a_index) const
	{
		return m_data[a_index];
	}

	inline void set(const _UINT32 & a_index, const DATA_TYPE & a_value)
	{
		m_data[a_index] = a_value;
	}

	inline void moveDown(const _UINT32 & a_from, const _UINT32 & a_offset, _UINT32 a_size)
	{
		for(int i = a_from-a_offset; i < a_size; ++i)
		{
			set(i+a_offset, get(i));
		}
	}
	inline void moveUp(const _UINT32 & a_from, const _UINT32 & a_offset, _UINT32 a_last)
	{
		for(int i = a_last-a_offset-1; i >= a_from; --i)
		{
			set(i+a_offset, get(i));
		}
	}

public:
	/** @param a_size reallocate the vector to this size. If smaller than allocated, shit is lost. */
	const bool allocateToSize(const _UINT32 & a_size)
	{
		// reallocate a new list with the given size
		DATA_TYPE * newList = new DATA_TYPE[a_size];
		// if the list could not allocate, fail...
		if(!newList)	return false;
		// the temp list is the one we will keep, while the old list will be dropped.
		DATA_TYPE * oldList = m_data;
		// swap done here so set(index, value) can be called instead of the equals operator
		m_data = newList;
		// if there is old data
		if(oldList)
		{
			int smallestSize = m_allocated<a_size?m_allocated:a_size;
			for(int i = 0; i < smallestSize; ++i)
			{
				set(i, oldList[i]);
			}
			delete [] oldList;
		}
		// mark the new allocated size (held size of oldList)
		m_allocated = a_size;
		return true;
	}

	/** note: this method is memory intesive, and should not be in any inner loops... */
	void add(const DATA_TYPE & a_value)
	{
		allocateToSize(size()+1);
		set(size()-1, a_value);
	}

	/** note: this method is memory intesive, and should not be in any inner loops... */
	DATA_TYPE * add()
	{
		allocateToSize(size()+1);
		return &get(size()-1);
	}

	/** sets all fields to an initial data state. WARNING: can cause memory leaks if used without care */
	inline void init()
	{
		m_data = 0;
		m_allocated = 0;
	}

	/** cleans up ITS OWN memory */
	inline void release()
	{
		if(m_data)
		{
			delete [] m_data;
			m_data = 0;
			m_allocated = 0;
		}
	}

	~GSArray(){release();}

	/** @return true if vector allocated this size */
	inline bool ensureCapacity(const _UINT32 & a_size)
	{
		if(a_size && m_allocated < a_size)
		{
			return allocateToSize(a_size);
		}
		return true;
	}

	/** @return true of the copy finished correctly */
	inline bool copy(const GSArray<DATA_TYPE> & a_array)
	{
		if(m_allocated != a_array.m_allocated)
		{
			release();
			allocateToSize(a_array.m_allocated);
		}
		for(int i = 0; i < a_array.m_allocated; ++i)
		{
			set(i, a_array.get(i));
		}
		return false;
	}

	/** copy constructor */
	inline GSArray(
		const GSArray<DATA_TYPE> & a_array)
	{
		init();
		copy(a_array);
	}

	/** default constructor allocates no list (zero size) */
	inline GSArray(){init();}


	/** size constructor */
	inline GSArray(const _UINT32 & a_size)
	{
		init();
		ensureCapacity(a_size);
	}

	/** format constructor */
	inline GSArray(const _UINT32 & a_size,
		const DATA_TYPE & a_defaultValue)
	{
		init();
		ensureCapacity(a_size);
		for(int i = 0; i < a_size; ++i)
			set(i, a_defaultValue);
	}

	/** @return the size of the list */
	inline const _UINT32 & size() const
	{
		return m_allocated;
	}

	/** @return the last value in the list */
	inline DATA_TYPE & getLast()
	{
		return get(size()-1);
	}

	/**
	 * @return the raw pointer to the data... 
	 * @note dangerous accessor. use it only if you know what you're doing.
	 */
	inline DATA_TYPE * getRawList()
	{
		return m_data;
	}

	/** 
	 * @param a_index is overwritten by the next element, which is 
	 * overwritten by the next element, and so on, till the last element
	 * @note this operation is memory intensive!
	 */
	void remove(const _UINT32 & a_index)
	{
		moveDown(a_index, -1, size());
		allocateToSize(m_allocated-1);
	}

	/** 
	 * @param a_index where to insert a_value. shifts elements in the vector.
	 * @note this operation is memory intensive!
	 */
	void insert(const _UINT32 & a_index, const DATA_TYPE & a_value)
	{
		setSize(m_size+1);
		moveUp(m_data, a_index, 1, size());
		set(a_index, a_value);
	}

	/** swaps to elements in the vector */
	inline void swap(const _UINT32 & a_index0, const _UINT32 & a_index1)
	{
		DATA_TYPE temp = get(a_index0);
		set(a_index0, get(a_index1));
		set(a_index1, temp);
	}

	/** @return index of 1st a_value at or after a_startingIndex. uses == */
	inline _UINT32 indexOf(const DATA_TYPE & a_value, const _UINT32 & a_startingIndex, const _UINT32 & a_endingIndex) const
	{
		for(int i = a_startingIndex; i < a_endingIndex; ++i)
		{
			if(get(i) == a_value)
				return i;
		}
		return -1;
	}

	/** @return index of 1st a_value at or after a_startingIndex. uses == */
	inline _UINT32 indexOf(const DATA_TYPE & a_value) const
	{
		return indexOf(a_value, 0, size());
	}
};




};
};

#endif
