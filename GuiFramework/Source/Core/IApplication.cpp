#include "Gui.h"
#include "Core/IApplication.h"

IApplication::IApplication(int argc, char** argv) : mp_mainWindow(nullptr) { }

void IApplication::onTick(float deltaTime) {

	if (mp_mainWindow != nullptr) {
		mp_mainWindow->onTick(deltaTime);
	}
}

void IApplication::onBegin() {
	
	// load all members of functional classes
	for (IFunctional* p_functional : mp_functional) {
		p_functional->loadMembers(getIniPath());
	}
}

void IApplication::onClose() {

	// save all members of functional classes
	for (IFunctional* p_functional : mp_functional) {
		p_functional->saveMembers(getIniPath());
	}
}

void IApplication::setMainWindow(MainWindow* p_mainWindow) {

	mp_mainWindow = p_mainWindow;
}

void IApplication::addFunctional(IFunctional* p_functional) {

	mp_functional.push_back(p_functional);
}
