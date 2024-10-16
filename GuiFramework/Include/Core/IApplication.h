#pragma once
#include "Gui.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"

class GUI_API IApplication {

private:
	MainWindow<Graphics2D>* mp_mainWindow;

public:
	IApplication(int argc, char** argv);

public:
	virtual int exec() = 0;
	void onTick(float deltaTime);

	void setMainWindow(MainWindow<Graphics2D>* p_mainWindow);
};