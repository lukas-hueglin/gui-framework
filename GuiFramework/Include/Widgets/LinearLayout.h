#pragma once
#include "Widgets/Layout.h"
#include <vector>

class GUI_API LinearLayout : public Layout {

private:
	Orientation m_orientation;

public:
	LinearLayout(Window<Graphics2D>* p_parent, Orientation orientation);

public:
	void onResize(Math::Rect availableRect) override;
};