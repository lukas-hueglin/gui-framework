#pragma once
#include "Gui.h"

namespace Math {

	struct GUI_API Point2D {
		float x;
		float y;

		Point2D(float x, float y);
	};

	struct GUI_API Rect {
		float left;
		float right;
		float top;
		float bottom;

		Rect(float left, float right, float top, float bottom);
		Rect(RECT& rect);
	};

	Rect expandRect(Rect& rect, float offset);
	Rect shrinkRect(Rect& rect, float offset);
}