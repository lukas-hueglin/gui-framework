#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"

template<class GRAPHICS_TYPE>
class GUI_API IWindow {
protected:
	GRAPHICS_TYPE* mp_graphics;

	Math::Rect m_rect;

public:
	IWindow();
	~IWindow();
	
public:
	template<class DERIVED_TYPE>
	static DERIVED_TYPE* create(std::wstring title);

protected:
	void onBegin();
	void onPaint();
	void onDestroy();
	void onResize(Math::Rect rect);

private:
	virtual void initialize(std::wstring title) = 0;

	// make all other templated IWindow classes a friend
	friend class IWindow;
};