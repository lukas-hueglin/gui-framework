#pragma once
#include "Platform/Win32/Win32Window.h"

template<class GRAPHICS_TYPE>
class GUI_API Win32MainWindow : public Win32Window<GRAPHICS_TYPE> {

public:
	static Win32MainWindow<GRAPHICS_TYPE>* create(const wchar_t* title);

private:
	PCWSTR getClassName() override;
	LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};