#pragma once
#include "Gui.h"

class GUI_API IGraphics {

private:
	virtual void createGraphicsResources() = 0;
	virtual void discardGraphicsResources() = 0;
};