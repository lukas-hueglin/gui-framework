#include "Application.h"
#include "Functional.h"

int main(int argc, char** argv) {
	
	// create new application
	Application* app = new Application(argc, argv);

	return app->exec();
}