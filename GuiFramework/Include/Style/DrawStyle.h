#pragma once

#ifdef WIN32
	#include "Style/IDrawStyle.h"
	using DrawStyle = IDrawStyle; // replace with actual windows implementation
#endif