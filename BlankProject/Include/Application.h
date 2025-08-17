#pragma once
#include "Core/IApplication.h"
#include "Functional.h"

class Application : public IApplication {

private:
	Functional& m_functional;

public:
	Application(int argc, char** argv);

private:
	void initUI() override;

	std::wstring getApplicationName();
};