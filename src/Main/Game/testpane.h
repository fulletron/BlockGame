#ifndef __TESTPANE_H_
#define __TESTPANE_H_

#include <Graphics/panel.h>
#include "fpscounter.h"

class TestPane : public GS::Graphics::Pane
{
selective:
public:
	TestPane(){}	

	_BOOL isDirty();
	void draw();	
	_BOOL handledInput(){}
};

#endif
