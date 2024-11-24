#pragma once
#include "Core/Application.h"

class App : public Application {

public:
	App(int argc, char** argv);

private:
	std::wstring getApplicationName();
};