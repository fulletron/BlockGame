#ifndef __PRESENTABLE_H_
#define __PRESENTABLE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace Game {

class IPresentable
{
public:
	virtual _BOOL isDirty() const = 0;
	virtual void setDirty(_BOOL a_dirty) = 0;
	virtual _UNION8 getPresentationElement8(const _UINT32 & a_index) = 0;
	//virtual _UNION16 getPresentationElement16() = 0;
};

class Presentable : public IPresentable
{
selective:
	_BOOL m_dirty;
public:
	/**
	* Check the dirty state of a presentable to see if it needs to be redrawn
	*/
	_BOOL isDirty() const {return m_dirty;}

	/**
	* Set the dirty state of the presentable
	*/
	void setDirty(_BOOL a_dirty) {m_dirty = a_dirty;}

	virtual _UNION8 getPresentationElement8(const _UINT32 & a_index) { _UNION8 a; a.asInt32 = 0; return a;  }
	// TODO :: virtual ? getPresentationBlock() = 0;
	// TODO :: virtual _UNION8 getPresentationElement8() = 0;
	// TODO :: virtual _UNION16 getPresentationElement16() = 0;
};

/* 

// KYLE :: TODO :: I DON'T KNOW IF I WANT TO USE THIS. THIS DOESN'T TRANSLATE
// WELL TO CUSTOM CLASSES, AND BEING ABLE TO SET DIRTY FROM WITHIN THE CLASS

template<typename DATA_TYPE>
class Presentable
{
public:	
	DATA_TYPE & dereference()
	{
		return m_data;
	}

	DATA_TYPE * pointer()
	{
		return &m_data;
	}

	bool isDirty()
	{
		return m_dirty;
	}

	void setDirty(bool a_dirty)
	{
		m_dirty = a_dirty;
	}

private:
	DATA_TYPE m_data;
	bool m_dirty;
};


*/

};
};

#endif
