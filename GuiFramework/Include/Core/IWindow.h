#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Common/EventUtils.h"

// forward declare layout
class Layout;

template<class GRAPHICS_TYPE>
class GUI_API IWindow {
protected:
	GRAPHICS_TYPE* mp_graphics;
	Math::Rect m_rect;

	Layout* mp_layout;
	bool m_layoutMouseHover;

public:
	IWindow();
	~IWindow();
	
public:
	template<class DERIVED_TYPE>
	static DERIVED_TYPE* create(const wchar_t* title);

	void setLayout(Layout* p_layout);

	GRAPHICS_TYPE* getGraphics();

protected:
	void onTick(float deltaTime);

	void onBegin();
	void onPaint();
	void onDestroy();
	void onResize(Math::Rect rect);
	void onMouseMove(Math::Point2D point);
	void onMouseDown(bool doubleClk);
	void onMouseRelease();

	void onKeyDown(Key key);
	void onKeyDown(char key);

private:
	virtual void initialize(const wchar_t* title) = 0;

	// make all other templated IWindow classes a friend
	friend class IWindow;
	friend class IApplication;
};