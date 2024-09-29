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
private:
	Graphics2D* mp_graphics;

	Math::Rect m_minSize;
	Math::Rect m_usedRect;
	Math::Rect m_hitboxRect;

	float m_margin;
	float m_padding;

	Alignment m_alignment;
	FillMode m_fillMode;

	bool m_mouseHover;
	bool m_mouseDown;

public:
	Widget(Window<Graphics2D>* p_parent);

	void onPaint();
	void onResize(Math::Rect availableRect);
	void onMouseHover(Math::Point2D point);
	void onMouseEnter();
	void onMouseLeave();
	void onMouseDown();
	void onMouseRelease();

	void setMargin(float margin);
	void setPadding(float padding);

	bool isMouseHovering();

	Math::Rect getHitbox();
};