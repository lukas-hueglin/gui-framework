#include "Gui.h"
#include "Common/MathUtils.h"

Math::Point2D::Point2D(float x, float y) : x(x), y(y) { }

Math::Rect::Rect(float left, float right, float top, float bottom) : left(left), right(right), top(top), bottom(bottom) { }

Math::Rect::Rect(RECT& rect) : left(rect.left), right(rect.right), top(rect.top), bottom(rect.bottom) { }

float Math::Rect::getWidth() {
	return right - left;
}

float Math::Rect::getHeight() {
	return bottom - top;
}

Math::Point2D Math::Rect::getCenter() {
	return Math::Point2D((left + right)/2, (top + bottom)/2);
}

Math::Size::Size(float width, float height) : width(width), height(height) { }

Math::Size Math::Size::operator+(Size b) {
	return Math::Size(width + b.width, height + b.height);
}


Math::Rect Math::expandRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left - offset, rect.right + offset, rect.top - offset, rect.bottom + offset);
}

Math::Rect Math::shrinkRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left + offset, rect.right - offset, rect.top + offset, rect.bottom - offset);
}

bool Math::pointInRect(Rect rect, Point2D point) {

	return rect.left < point.x && rect.right > point.x && rect.top < point.y && rect.bottom > point.y;
}
