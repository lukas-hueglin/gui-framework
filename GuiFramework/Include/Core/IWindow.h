#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"

// forward declare widget
class Widget;

template<class GRAPHICS_TYPE>
class GUI_API IWindow {
protected:
	GRAPHICS_TYPE* mp_graphics;
	Widget* mp_widget;

	Math::Rect m_rect;

public:
	IWindow();
	~IWindow();
	
public:
	template<class DERIVED_TYPE>
	static DERIVED_TYPE* create(const wchar_t* title);

	void setWidget(Widget* p_widget);

	GRAPHICS_TYPE* getGraphics();

protected:
	void onBegin();
	void onPaint();
	void onDestroy();
	void onResize(Math::Rect rect);
	void onMouseMove(Math::Point2D point);
	void onMouseDown();
	void onMouseRelease();

private:
	virtual void initialize(const wchar_t* title) = 0;

	// make all other templated IWindow classes a friend
	friend class IWindow;
};