#pragma once

#ifdef WIN32
	#include "Core/IWindow.h"
	template<class GRAPHICS_TYPE>
	using Window = IWindow<GRAPHICS_TYPE>; // replace with actual windows implentation
#endif