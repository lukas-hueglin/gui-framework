#include "Gui.h"
#include "Core/IApplication.h"

IApplication::IApplication(int argc, char** argv) : mp_mainWindow(nullptr) { }

void IApplication::onTick(float deltaTime) {

	if (mp_mainWindow != nullptr) {
		mp_mainWindow->onTick(deltaTime);
	}
}

void IApplication::setMainWindow(MainWindow<Graphics2D>* p_mainWindow) {

	mp_mainWindow = p_mainWindow;
}
