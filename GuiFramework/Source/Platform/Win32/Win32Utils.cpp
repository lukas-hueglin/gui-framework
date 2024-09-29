#include "Gui.h"
#include "Platform/Win32/Win32Utils.h"

D2D1_POINT_2F Win32Utils::D2D1Point(Math::Point2D& point) {

    return D2D1::Point2F(point.x, point.y);
}

D2D1_RECT_F Win32Utils::D2D1Rect(Math::Rect& rect) {

    return D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom);
}

D2D1_COLOR_F Win32Utils::D2D1Color(Color& color){

    return D2D1::ColorF(color.r, color.g, color.b, color.a);
}
