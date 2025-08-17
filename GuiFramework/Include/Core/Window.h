#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Common/EventUtils.h"
#include "Core/Graphics2D.h"

#include "Common/Pimpl.h"
#include "Core/Object.h"

//class Layout;
//class DropDown;

class GUI_API Window : public Object {

	ADD_IMPL_CLASS_PARENT()

private:
	Graphics2D* mp_graphics;
	std::wstring m_windowName;
	Math::Rect m_rect;

	//Layout* mp_layout;
	//DropDown* mp_dropDown;
	bool m_layoutMouseHover;
	bool m_dropDownMouseHover;

public:
	Window(const Credentials& creds, IApplication* p_app, std::wstring windowName);
	~Window();

public:
	//void setLayout(Layout* p_layout);

	//void registerDropDown(DropDown* p_dropDown);
	//void unregisterDropDown();

	Graphics2D* getGraphics();

private:
	void onTick(float deltaTime);

	void onInitialize();
	void onBegin();
	void onClose();

	void onPaint();
	void onResize(Math::Rect rect);
	void onMouseMove(Math::Point2D point);
	void onMouseDown(bool doubleClk, Math::Point2D point);
	void onMouseRelease(Math::Point2D point);

	void onMouseScroll(bool up, bool shift, bool ctr);

	void onKeyDown(Key key);
	void onKeyDown(char key);

	// make IApplication a friend class
	friend class IApplication;
};