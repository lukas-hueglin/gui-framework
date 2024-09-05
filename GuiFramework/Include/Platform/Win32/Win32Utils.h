#pragma once
#include "Gui.h"

namespace Win32Utils {

    template<class T>
    void safeRelease(T** ppT) {

        if (*ppT) {

            (*ppT)->Release();
            *ppT = NULL;
        }
    }
}