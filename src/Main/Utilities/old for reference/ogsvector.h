#ifndef __GSVECTOR_H_
#define __GSVECTOR_H_

#include "gsarray.h"

namespace GS {
namespace UtilitiesNS {


typedef bool (*CompareFunction)(void * a_leftWinsTrue, void *);

template<typename DATA_TYPE>
class GSVector : public GSArray<DATA_TYPE>
{
private:
	void __mergeSorting(DATA_TYPE * a_data, int left, int right, DATA_TYPE * scratch, CompareFunction a_compFunc)
	{
		if(right == left + 1)
			return;
		else
		{
			int i = 0;
			int length = right - left;
			int midpoint_distance = length/2;
			int l = left, r = left + midpoint_distance;

			__mergeSorting(a_data, left, left + midpoint_distance, scratch, a_compFunc);
			__mergeSorting(a_data, left + midpoint_distance, right, scratch, a_compFunc);

			for(i = 0; i < length; ++i)
			{
				if( l < left + midpoint_distance && ( r == right || a_compFunc((void*)a_data[l],(void*)a_data[r]) == true) )
				{
					scratch[i] = a_data[l];
					l++;
				}
				else
				{
					scratch[i] = a_data[r];
					r++;
				}
			}

			for(i = left; i < right; i++)
			{
				a_data[i] = scratch[i - left];
			}
		}
	}

protected:
	/** the default size to allocate new vectors to */
	static const int DEFAULT_ALLOCATION_SIZE = 10;

	/** number of valid elements that the caller thinks we have.. */
	int m_size;

public:
	/** sets all fields to an initial data state. WARNING: can cause memory leaks if used without care */
	inline void init()
	{
		GSArray<DATA_TYPE>::init();
		m_size = 0;
	}

	/** cleans up memory */
	inline void release()
	{
		GSArray<DATA_TYPE>::release();
		m_size = 0;
	}

	/** @return true of the copy finished correctly */
	inline bool copy(const GSVector<DATA_TYPE> & a_vector)
	{
		if(ensureCapacity(a_vector.m_size))
		{
			for(int i = 0; i < a_vector.m_size; ++i)
			{
				set(i, a_vector.get(i));
			}
			m_size = a_vector.m_size;
			return true;
		}
		return false;
	}

	/** copy constructor */
	inline GSVector(
		const GSVector<DATA_TYPE> & a_vector)
	{
		init();
		copy(a_vector);
	}

	/** default constructor allocates no list (zero size) */
	inline GSVector(){init();}

	/** add an array to this vector */
	inline void add(const int & a_size,
		const DATA_TYPE * a_values)
	{
		ensureCapacity(size()+a_size);
		for(int i = 0; i < a_size; ++i)
			add(a_values[i]);
	}

	/** format constructor */
	inline GSVector(const int & a_size,
		const DATA_TYPE & a_defaultValue)
	{
		init();
		add(a_size, a_defaultValue);
	}

	/** complete constructor */
	inline GSVector(const int & a_size,
		DATA_TYPE * const & a_defaultValues)
	{
		init();
		ensureCapacity(a_size);
		for(int i = 0; i < a_size; ++i)
			add(a_defaultValues[i]);
	}

	/** @return the last value in the list */
	inline DATA_TYPE & getLast()
	{
		return m_data[m_size-1];
	}

	/** @return the last added value in the list, and lose that value */
	inline DATA_TYPE & pop()
	{
		return m_data[--m_size];
	}

	/**
	 * @param value to add to the list 
	 * @note adding a value may cause memory allocation
	 */
	void add(const DATA_TYPE & a_value)
	{
		// where am i storing these values?
		// if i don't have a place to store them, i better make one.
		if(m_data == 0)
		{
			// make a new list to store numbers in
			allocateToSize(DEFAULT_ALLOCATION_SIZE);
		}
		// if we don't have enough memory allocated for this list
		if(m_size >= m_allocated)
		{
			// make a bigger list
			allocateToSize(m_allocated*2);
		}
		set(m_size, a_value);
		m_size++;
	}

	/**
	 * @param a_value to add to the list if it isnt in the list already
	 * @return true the index where the element exists
	 */
	int addNoDuplicates(const DATA_TYPE & a_value)
	{
		int index = indexOf(a_value);
		if(index < 0)
		{
			index = m_size;
			add(a_value);
		}
		return index;
	}

	/** @param a_vector a vector to add all the elements from */
	inline void addVector(const GSVector<DATA_TYPE> & a_vector)
	{
		for(int i = 0; i < a_vector.size(); ++i)
		{
			add(a_vector.get(i));
		}
	}

	/** @return the size of the list */
	inline const int & size() const
	{
		return m_size;
	}

	/** 
	 * @param size the user wants the vector to be (chopping off elements)
	 * @return false if could not allocate memory
	 * @note may cause memory allocation if size is bigger than current
	 */
	inline bool setSize(const int & a_size)
	{
		if(!ensureCapacity(a_size))
			return false;
		m_size = a_size;
		return true;
	}

	/** sets size to zero, but does not deallocate any memory */
	inline void clear()
	{
		setSize(0);
	}

	/** 
	 * @param a_index is overwritten by the next element, which is 
	 * overwritten by the next element, and so on, till the last element
	 */
	void remove(const int & a_index)
	{
		moveDown(a_index, -1, m_size);
		setSize(m_size-1);
	}

	/** 
	 * @param a_index where to insert a_value. shifts elements in the vector.
	 */
	void insert(const int & a_index, const DATA_TYPE & a_value)
	{
		setSize(m_size+1);
		moveUp(a_index, 1, m_size);
		set(a_index, a_value);
	}

	/** 
	 * @return first element from the list and moves the rest up 
	 * @note removes the first element from the list
	 */
	inline const DATA_TYPE pull()
	{
		DATA_TYPE value = get(0);
		remove(0);
		return value;
	}

	/** @param a_index is replaced by the last element, then size is reduced. */
	inline void removeFast(const int & a_index)
	{
		swap(a_index, m_size-1);
		setSize(m_size-1);
	}

	/** @return the index of the first appearance of a_value in this vector. uses == */
	inline int indexOf(const DATA_TYPE & a_value) const
	{
		for(int i = 0; i < m_size; ++i)
		{
			if(get(i) == a_value)
				return i;
		}
		return -1;
	}

	/** @return index of 1st a_value at or after a_startingIndex. uses == */
	inline int indexOf(const DATA_TYPE & a_value, const int & a_startingIndex) const
	{
		return indexOf(a_value, a_startingIndex, m_size);
	}


	/**
	 * @param a_value first appearance replaced by last element. breaks if not in list
	 */
	inline void removeDataFast(const DATA_TYPE & a_value)
	{
		removeFast(indexOf(a_value));
	}

	/**
	 * @param a_listToExclude removes these elements from *this list
	 * @return true if at least one element was removed
	 */
	inline bool removeListFast(const GSVector<DATA_TYPE> & a_listToExclude)
	{
		bool aTermWasRemoved = false;
		for(int e = 0; e < a_listToExclude.size(); ++e)
		{
			for(int i = 0; i < size(); ++i)
			{
				if(a_listToExclude.get(e) == get(i))
				{
					removeFast(i);
					--i;
					aTermWasRemoved = true;
				}
			}
		}
		return aTermWasRemoved;
	}

	/** @param a_value first appearance is removed. breaks if not in list */
	inline void removeData(const DATA_TYPE & a_value)
	{
		remove(indexOf(a_value));
	}

	/** destructor */
	inline ~GSVector()
	{
		release();
	}

	inline void mergeSort(CompareFunction a_CompareFunc)
	{

		for(int i = 0; i < size() - 1; ++i)
		{
			if(a_CompareFunc(get(i), get(i+1)))
			{
				/// SOME KIND OF SWAPPAGE
			}
		}
	}

	inline bool sort(CompareFunction a_CompareFunc)
	{
		DATA_TYPE * scratch = new DATA_TYPE[size()];

		if(scratch != 0)
		{
			__mergeSorting(m_data, 0, size(), scratch, a_CompareFunc);
			delete [] scratch;
			return true;
		}
		else
		{
			return false;
		}
	}
};



};
};

#endif