#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Common/EventUtils.h"
#include "Core/GeometryResource.h"
#include "Core/Graphics2D.h"

// forward declare layout
class Layout;

class GUI_API IWindow {
protected:
	Graphics2D* mp_graphics;
	Math::Rect m_rect;

	Layout* mp_layout;
	bool m_layoutMouseHover;

private:
	GeometryResource* mp_backgroundResource;

public:
	IWindow();
	~IWindow();
	
public:
	template<class DERIVED_TYPE>
	static DERIVED_TYPE* create(std::wstring title);

	void setLayout(Layout* p_layout);

	Graphics2D* getGraphics();

protected:
	void onTick(float deltaTime);

	void onBegin();
	void onPaint();
	void onDestroy();
	void onResize(Math::Rect rect);
	void onMouseMove(Math::Point2D point);
	void onMouseDown(bool doubleClk, Math::Point2D point);
	void onMouseRelease(Math::Point2D point);

	void onKeyDown(Key key);
	void onKeyDown(char key);

private:
	virtual void initialize(std::wstring title) = 0;

	// make all other templated IWindow classes a friend
	friend class IWindow;
	friend class IApplication;
};