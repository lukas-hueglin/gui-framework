#pragma once
#include "Gui.h"

class GUI_API IApplication {

public:
	IApplication(int argc, char** argv);

public:
	virtual int exec() = 0;
};