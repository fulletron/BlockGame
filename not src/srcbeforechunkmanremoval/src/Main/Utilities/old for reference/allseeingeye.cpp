//======HEADER  "testclass.h" =============
#ifndef __TESTCLASS_H_
#define __TESTCLASS_H_

class TestClass
{
public:
	TestClass();
	char* getName();
private:
	char * m_name;
};

#endif
//===========================================
//=======SOURCE "testclass.cpp"============
#include "testclass.h"

TestClass::TestClass()
{
	m_name = "Test";
}

char * TestClass::getName()
{
	return m_name;
}
//===========================================