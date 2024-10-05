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

		float getWidth();
		float getHeight();
		Point2D getCenter();
	};

	struct GUI_API Size {
		float width;
		float height;

		Size(float width, float height);

		Size operator+(Size b);
	};

	Rect expandRect(Rect& rect, float offset);
	Rect shrinkRect(Rect& rect, float offset);

	bool pointInRect(Rect rect, Point2D point);
}