#pragma once
#include "../Parser/Namescope.h"
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <stdexcept>

class Widget;

class AppRef
{
public:
	static std::vector< std::pair<Widget*, float> > *widgetsPtr;

	static void InitGraphSystem(std::vector< std::pair<Widget*, float> > *_widgetsPtr)
	{
		AppRef::widgetsPtr = _widgetsPtr;
	}
};

double f_graph(Namescope*, const std::vector<std::shared_ptr<Value>>&);