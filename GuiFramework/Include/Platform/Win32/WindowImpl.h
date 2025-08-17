#pragma once
#include "Core/Window.h"

class GUI_API Window::Impl {

    LINK_DEFINITION(Window)

protected:
	HWND m_hWnd;

public:
	Impl(Window& def);
	~Impl();

public:
    void initialize(std::wstring windowName);

private:
    void createHwnd(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    );

	static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    virtual PCWSTR getClassName();
};