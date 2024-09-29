#include "Gui.h"
#include "Common/MathUtils.h"

Math::Point2D::Point2D(float x, float y) : x(x), y(y) { }

Math::Rect::Rect(float left, float right, float top, float bottom) : left(left), right(right), top(top), bottom(bottom) { }

Math::Rect::Rect(RECT& rect) : left(rect.left), right(rect.right), top(rect.top), bottom(rect.bottom) { }

Math::Rect Math::expandRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left - offset, rect.right + offset, rect.top - offset, rect.bottom + offset);
}

Math::Rect Math::shrinkRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left + offset, rect.right - offset, rect.top + offset, rect.bottom - offset);
}
