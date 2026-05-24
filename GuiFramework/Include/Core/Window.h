#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Common/EventUtils.h"
#include "Core/Object.h"

class Widget;
//class DropDown;

class GUI_API Window : public Object {

private:
	std::wstring m_windowName;
	Math::Rect m_rect;

	Widget* mp_widget;
	//DropDown* mp_dropDown;
	bool m_widgetMouseHover;
	bool m_dropDownMouseHover;

// Win32 members
protected:
	HWND m_hWnd;

	// underlying graphics infrastructure
	ID3D11Device* mp_d3d11Device;
	IDXGIDevice* mp_dxgiDevice;

	// direct 2d
	ID2D1Device* mp_d2d1Device;

	// direct composition
	IDCompositionDevice* mp_dcompDevice;
	IDCompositionTarget* mp_dcompTarget;


public:
	Window(const Credentials& creds, IApplication* p_app, std::wstring windowName);
	~Window();

public:
	void setWidget(Widget* p_widget);

	//void registerDropDown(DropDown* p_dropDown);
	//void unregisterDropDown();

private:
	void onTick(float deltaTime) override;

	void onInitialize() override;
	void onBegin() override;
	void onClose() override;

	void onPaint();
	void onResize(Math::Rect rect);
	void onMouseMove(Math::Point2D point);
	void onMouseDown(bool doubleClk, Math::Point2D point);
	void onMouseRelease(Math::Point2D point);

	void onMouseScroll(bool up, bool shift, bool ctr);

	void onKeyDown(Key key);
	void onKeyDown(char key);

	void messageBox(const std::wstring& title, const std::wstring& text);

// Win32 methods
private:
	HRESULT createHwnd(
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

	HRESULT initializeGraphicsResources();

	HRESULT handleUpdate();

	HRESULT setTargetRoot(IDCompositionVisual* p_visual);

	static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual PCWSTR getClassName();

	// make friend classes
	friend class IApplication;
	friend class Widget;
	friend class Widget2d;
};