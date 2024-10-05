#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Core/Graphics2D.h"

enum GUI_API Alignment {
	TopLeft = 0,
	TopCenter = 1,
	TopRight = 2,
	CenterLeft = 3,
	Center = 4,
	CenterRight = 5,
	BottomLeft = 6,
	BottomCenter = 7,
	BottomRight = 8
};

enum GUI_API FillMode {
	Expand = 0,
	Shrink = 1
};

class GUI_API Widget {
protected:
	Graphics2D* mp_graphics;

	Math::Size m_minSize;
	Math::Rect m_usedRect;
	Math::Rect m_hitboxRect;
	Math::Rect m_contentRect;

	float m_margin;
	float m_padding;

	Alignment m_alignment;
	FillMode m_fillMode;

	bool m_mouseHover;
	bool m_mouseDown;

public:
	Widget(Window<Graphics2D>* p_parent);

	virtual void onPaint();
	void onResize(Math::Rect availableRect);

	virtual void onMouseHover(Math::Point2D point);
	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseDown();
	virtual void onMouseRelease();

	void setMargin(float margin);
	void setPadding(float padding);
	void setAlignment(Alignment alignment);
	void setFillMode(FillMode fillMode);

	bool isMouseHovering();

	Math::Rect getHitbox();
};