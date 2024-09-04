#pragma once

#ifdef WIN32
	#include "Core/IGraphics2D.h"
	using Graphics2D = IGraphics2D; // replace with actual windows implementation
#endif