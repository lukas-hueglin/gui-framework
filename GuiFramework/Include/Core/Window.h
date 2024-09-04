#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32Window.h"
	template<class GRAPHICS_TYPE>
	using Window = Win32Window<GRAPHICS_TYPE>;
#endif