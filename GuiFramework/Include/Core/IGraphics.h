#pragma once
#include "Gui.h"
#include "Core/IWindow.h"

class GUI_API IGraphics {

public:
	virtual void createGraphicsResources() = 0;
	virtual void discardGraphicsResources() = 0;

	virtual void resizeCanvas() = 0;
};