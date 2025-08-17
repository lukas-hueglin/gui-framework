#include "Gui.h"
#include "Core/IApplication.h"

#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/IFunctional.h"

#include PLATFORM(IApplicationImpl.h)

IApplication::IApplication(int argc, char** argv) : mp_mainWindow(nullptr) {

	INIT_IMPL_CLASS(*this);
}

IApplication::~IApplication() {
	
	delete &IMPL;

	for (Window* p_window : mp_windows) {
		delete p_window;
	}

	for (IFunctional* p_functional : mp_functionals) {
		delete p_functional;
	}
}

void IApplication::onTick(float deltaTime) {

	for (Window* p_window : mp_windows) {
		p_window->onTick(deltaTime);
	}

	for (IFunctional* p_functional : mp_functionals) {
		p_functional->onTick(deltaTime);
	}
}

void IApplication::onBegin() {

	for (IFunctional* p_functional : mp_functionals) {
		p_functional->onBegin();
		p_functional->loadMembers(IMPL.getIniPath());
	}
}

void IApplication::onClose() {

	// save all members of functional classes
	for (Window* p_window : mp_windows) {
		p_window->onClose();
	}

	for (IFunctional* p_functional : mp_functionals) {
		p_functional->onClose();
		p_functional->saveMembers(IMPL.getIniPath());
	}
}

int IApplication::exec() {

	// init windows and widgets
	initUI();

	// run program
	onBegin();
	IMPL.programLoop();
	onClose();

	return 0;
}

void IApplication::registerObject(Window* p_window) {

	mp_windows.push_back(p_window);
}

void IApplication::registerObject(IFunctional* p_functional) {

	mp_functionals.push_back(p_functional);
}

void IApplication::invokeApplicationClose() {

	IMPL.invokeClose();
}

void IApplication::invokeWindowClose(Window* p_window) {

	p_window->onClose();
	mp_windows.remove(p_window);
	delete p_window;

	if (mp_windows.size() == 0) {
		invokeApplicationClose();
	}
}
