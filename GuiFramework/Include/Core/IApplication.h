#pragma once
#include "Gui.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"
#include "Core/IFunctional.h"

#include <vector>

class GUI_API IApplication {

private:
	MainWindow* mp_mainWindow;
	std::vector<IFunctional*> mp_functional;

public:
	IApplication(int argc, char** argv);

public:
	virtual int exec() = 0;

	void setMainWindow(MainWindow* p_mainWindow);
	void addFunctional(IFunctional* p_functional);

protected:

	void onTick(float deltaTime);
	virtual void onBegin();
	virtual void onClose();

	virtual std::wstring getApplicationName() = 0;
	virtual std::wstring getIniPath() = 0;
};