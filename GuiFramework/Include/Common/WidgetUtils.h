#pragma once
#include "Gui.h"


enum GUI_API Alignment : int {
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

enum GUI_API Orientation {
	Horizontal = 0,
	Vertical = 1
};

enum GUI_API Justification : int {
	Leading = 0,
	Middle = 1,
	Trailing = 2
};

Justification getJustification(Alignment& alignment, Orientation& orientation);