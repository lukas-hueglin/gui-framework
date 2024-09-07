#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32MainWindow.h"
	template<class GRAPHICS_TYPE>
	using MainWindow = Win32MainWindow<GRAPHICS_TYPE>;
#endif