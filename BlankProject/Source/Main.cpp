#include "Core/Application.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"
#include "Widgets/Button.h"

#include "Windows.h"

void func() {
	MessageBox(NULL, L"Hello, World!", L"Important Message", NULL);
}

int main(int argc, char** argv) {
	
	// create new application
	Application* app = new Application(argc, argv);

	// create new window
	const wchar_t* s = L"Window";
	MainWindow<Graphics2D>* window = MainWindow<Graphics2D>::create(s);

	// create a widget
	Button* w = new Button(window, L"Label");
	w->setMargin(10);
	w->setPadding(10);
	w->connect(func);

	window->setWidget(w);

	return app->exec();
}