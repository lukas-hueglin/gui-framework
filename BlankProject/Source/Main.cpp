#include "Core/Application.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"

int main(int argc, char** argv) {
	
	// create new application
	Application* app = new Application(argc, argv);

	// create new window
	std::wstring s = L"Window";
	MainWindow<Graphics2D>* window = MainWindow<Graphics2D>::create(s);

	return app->exec();
}