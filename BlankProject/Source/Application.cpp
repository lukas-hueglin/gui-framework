#include "Gui.h"
#include "Application.h"

App::App(int argc, char** argv) : Application(argc, argv) { }

std::wstring App::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
