#include "Gui.h"
#include "Application.h"

#include "Core/Window.h"
#include "Widgets/Label.h"
#include "Widgets/LinearLayout.h"

#include <numbers>
#include <string>

Application::Application(int argc, char** argv) : IApplication(argc, argv), m_functional(create<Functional>()) { }

void Application::initUI() {

	// create new window
	Window& window = create<Window>(L"Window");

	// create background
	LinearLayout& layout = create<LinearLayout>(&window, nullptr, Orientation::Horizontal);

	window.setWidget(&layout);

	// create Label
	Label& label1 = create<Label>(&window, &layout, L"Hello, World!");
	layout.addWidget(&label1);
	Label& label2 = create<Label>(&window, &layout, L"This works!");
	layout.addWidget(&label2);

}

std::wstring Application::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
