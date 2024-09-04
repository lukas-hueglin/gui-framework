#pragma once
#include "Core/IWindow.h"

template<class GRAPHICS_TYPE>
class GUI_API Win32Window : public IWindow<GRAPHICS_TYPE> {

protected:
	HWND m_hWnd;

public:
	Win32Window();
	~Win32Window();

private:
    void initialize(std::wstring title) override;

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
    virtual PCWSTR getClassName();

protected:
	virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};