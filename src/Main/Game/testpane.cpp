#include "testpane.h"

_BOOL TestPane::isVisible()
{
	return true;
}

_BOOL TestPane::isDirty()
{
	return m_isDirty;
}

void TestPane::makeDirty()
{
	m_isDirty = true;
}

void TestPane::draw()
{
	// KYLE :: DO MAGIC
	m_isDirty = false;
}
