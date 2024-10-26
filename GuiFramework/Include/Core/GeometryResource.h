#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32GeometryResource.h"
	using GeometryResource = Win32GeometryResource;
#endif