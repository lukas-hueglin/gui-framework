#include "Gui.h"
#include "Platform/Win32/Win32Utils.h"

D2D1_POINT_2F Win32Utils::D2D1Point(Math::Point2D& point) {

    return D2D1::Point2F(point.x(), point.y());
}

D2D1_RECT_F Win32Utils::D2D1Rect(Math::Rect& rect) {

    return D2D1::RectF(rect.left(), rect.top(), rect.right(), rect.bottom());
}

D2D1_COLOR_F Win32Utils::D2D1Color(Color& color){

    return D2D1::ColorF(color.r, color.g, color.b, color.a);
}

Key Win32Utils::convertWin32Keys(WPARAM wParam) {

    if (wParam == 0x08) {
        return Key::Backspace;
    }
    else if (wParam == 0x09) {
        return Key::Tab;
    }
    else if (wParam == 0x0D) {
        return Key::Enter;
    }
    else if (wParam == 0x1B) {
        return Key::Esc;
    }
    else if (wParam == 0x2D) {
        return Key::Insert;
    }
    else if (wParam == 0x2E) {
        return Key::Delete;
    }
    else if (wParam >= 0x21 && wParam <= 0x28) {
        return static_cast<Key>(wParam);
    }
    else if (wParam >= 0x70 && wParam <= 0x7B) {
        return static_cast<Key>(wParam);
    }
    else {
        return Key::Empty;
    }
}
