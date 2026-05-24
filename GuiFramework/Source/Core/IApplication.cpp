#include "Gui.h"
#include "Core/IApplication.h"

#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/IFunctional.h"

#include <ShlObj.h>
#include <chrono>


IApplication::IApplication(int argc, char** argv) { }

IApplication::~IApplication() {

	for (Window* p_window : mp_windows) {
		delete p_window;
	}

	for (IFunctional* p_functional : mp_functionals) {
		delete p_functional;
	}
}

int IApplication::exec() {

	// init windows and widgets
	initUI();

	// run program
	onBegin();
	programLoop();
	onClose();

	return 0;
}

void IApplication::registerObject(Window* p_window) {

	mp_windows.push_back(p_window);
	mp_objects.push_back(p_window);
}

void IApplication::registerObject(IFunctional* p_functional) {

	mp_functionals.push_back(p_functional);
	mp_objects.push_back(p_functional);
}

void IApplication::registerObject(Object* p_object) {

	mp_objects.push_back(p_object);
}

void IApplication::invokeApplicationClose() {

	PostQuitMessage(0);
}

void IApplication::invokeWindowClose(Window* p_window) {

	p_window->onClose();
	mp_windows.remove(p_window);
	delete p_window;

	if (mp_windows.size() == 0) {
		invokeApplicationClose();
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
		p_functional->loadMembers(getIniPath());
	}

	for (Window* p_window : mp_windows) {
		p_window->onBegin();
	}
}

void IApplication::onClose() {

	// save all members of functional classes
	for (Window* p_window : mp_windows) {
		p_window->onClose();
	}

	for (IFunctional* p_functional : mp_functionals) {
		p_functional->onClose();
		p_functional->saveMembers(getIniPath());
	}
}

void IApplication::programLoop() {

	// setup console if debug mode
	SETUP_CONSOLE()

	// create time stamp and duration object
	std::chrono::time_point<std::chrono::system_clock> now, lastFrame;
	std::chrono::duration<float> deltaTime;
	lastFrame = std::chrono::system_clock::now();

	// get and translate windows message
	MSG msg = { };
	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			// handle Windows messages
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// measure time
			now = std::chrono::system_clock::now();
			deltaTime = now - lastFrame;

			if (deltaTime.count() >= 1.0f / 30.0f) {
				onTick(deltaTime.count());
				lastFrame = now;
			}
		}
	}
}

std::wstring IApplication::getIniPath() {

	// create a path
	PWSTR appDataLocal;
	HRESULT hr;

	// read app data location
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &appDataLocal);

	// create path
	std::wstringstream ss;
	ss << appDataLocal << L"\\" << getApplicationName();

	// Create Folder
	CreateDirectory(ss.str().c_str(), NULL);

	// add file name
	ss << L"\\" << getApplicationName() << L".ini";

	return ss.str();
}
