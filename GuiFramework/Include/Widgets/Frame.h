#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Core/Graphics2D.h"
#include "Common/WidgetUtils.h"


class GUI_API Frame {
protected:
	Graphics2D* mp_graphics;

	Math::Size m_minSize;
	Math::Rect m_usedRect;
	Math::Rect m_hitboxRect;
	Math::Rect m_contentRect;

	Alignment m_alignment;
	FillMode m_fillMode;

	float m_margin;
	float m_padding;

public:
	Frame(Window<Graphics2D>* p_parent);

#ifdef DEBUG_UI
	virtual void onPaint();
#else
	virtual void onPaint() = 0;
#endif

	virtual void onResize(Math::Rect availableRect);

	virtual void onMouseHover(Math::Point2D point) = 0;
	virtual void onMouseEnter() = 0;
	virtual void onMouseLeave() = 0;
	virtual void onMouseDown() = 0;
	virtual void onMouseRelease() = 0;

	float getMargin();
	float getPadding();
	Math::Size getMinSize();
	Alignment getAlignment();
	FillMode getFillMode();

	void setMargin(float margin);
	void setPadding(float padding);
	void setMinSize(Math::Size size);
	void setAlignment(Alignment alignment);
	void setFillMode(FillMode fillMode);

	Math::Rect getHitbox();
};