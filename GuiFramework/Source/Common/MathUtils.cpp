#include "Gui.h"
#include "Common/MathUtils.h"


Math::Rect Math::expandRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left() - offset, rect.right() + offset, rect.top() - offset, rect.bottom() + offset);
}

Math::Rect Math::shrinkRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left() + offset, rect.right() - offset, rect.top() + offset, rect.bottom() - offset);
}

bool Math::pointInRect(Rect rect, Point2D point) {

	return rect.left() < point.x() && rect.right() > point.x() && rect.top() < point.y() && rect.bottom() > point.y();
}
