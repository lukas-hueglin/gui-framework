#include "Gui.h"
#include "Application.h"

#include "Core/Window.h"
#include "Widgets/Label.h"

#include <numbers>
#include <string>

Application::Application(int argc, char** argv) : IApplication(argc, argv), m_functional(create<Functional>()) { }

void Application::initUI() {

	// create new window
	Window& window = create<Window>(L"Window");

	// create background
	Widget2d& background = create<Widget2d>(&window, nullptr);
	background.setFillMode(FillMode::Expand);
	window.setFrame(&background);

	// create Label
	//Label& label = create<Label>(&window, nullptr, L"Hello, World!");
	//window.setFrame(&label);

}

std::wstring Application::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
