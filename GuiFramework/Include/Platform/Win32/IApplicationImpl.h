#pragma once
#include "Core/IApplication.h"

class GUI_API IApplication::Impl {

	LINK_DEFINITION(IApplication)

public:
	Impl(IApplication& def);

public:
	int programLoop();
	std::wstring getIniPath();

	void invokeClose();
};