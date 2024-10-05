#pragma once
#include "Widgets/Widget.h"
#include <vector>

enum GUI_API Orientation {
	Horizontal = 0,
	Vertical = 1
};

class GUI_API LinearLayout : public Widget {
private:
	std::vector<Widget*> m_widgets;
	std::vector<float> m_weights;

	Orientation m_orientation;

	Widget* m_mouseHoverWidget;

public:
	LinearLayout(Window<Graphics2D>* p_parent, Orientation orientation);

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseLeave() override;
	void onMouseDown() override;
	void onMouseRelease() override;

	void addWidget(Widget* p_widget, float weight = 1.0f);
	void removeWidget(Widget* p_widget);
};