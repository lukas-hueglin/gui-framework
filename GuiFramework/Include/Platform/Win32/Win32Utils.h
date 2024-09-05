#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Style/Color.h"

namespace Win32Utils {

    // conversion functions
    D2D1_POINT_2F D2D1Point(Math::Point2D& point);
    D2D1_RECT_F D2D1Rect(Math::Rect& rect);
    D2D1_COLOR_F D2D1Color(Color& color);

    // safe release for direct2d objects
    template<class T>
    void safeRelease(T** ppT) {

        if (*ppT) {

            (*ppT)->Release();
            *ppT = NULL;
        }
    }
}