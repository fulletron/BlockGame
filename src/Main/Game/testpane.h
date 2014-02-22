#ifndef __TESTPANE_H_
#define __TESTPANE_H_

#include <Graphics/panel.h>

class TestPane : public GS::Graphics::IPane
{
selective:
	_BOOL m_isDirty;
public:
	TestPane() : m_isDirty(true) {}	

	_BOOL isVisible();
	_BOOL isDirty();
	void makeDirty();
	void draw();	
};

#endif
