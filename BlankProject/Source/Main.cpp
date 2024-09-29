#include "Core/Application.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"
#include "Widgets/Widget.h"

int main(int argc, char** argv) {
	
	// create new application
	Application* app = new Application(argc, argv);

	// create new window
	const wchar_t* s = L"Window";
	MainWindow<Graphics2D>* window = MainWindow<Graphics2D>::create(s);

	// create a widget
	Widget* w = new Widget(window);
	w->setMargin(10);
	window->setWidget(w);

	return app->exec();
}