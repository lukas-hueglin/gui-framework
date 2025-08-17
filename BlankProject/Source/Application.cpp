#include "Gui.h"
#include "Application.h"

#include "Core/Window.h"

#include <numbers>
#include <string>

Application::Application(int argc, char** argv) : IApplication(argc, argv), m_functional(create<Functional>()) { }

void Application::initUI() {

	// create new window
	std::wstring title = L"Window";
	Window& window = create<Window>(title);
}

std::wstring Application::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
