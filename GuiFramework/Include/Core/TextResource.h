#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32TextResource.h"
	using TextResource = Win32TextResource;
#endif