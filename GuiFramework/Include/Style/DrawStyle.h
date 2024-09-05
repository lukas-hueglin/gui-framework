#pragma once
#include "Gui.h"
#include "Style/Color.h"

class GUI_API DrawStyle {

private:
	Color* mp_edgeColor;
	Color* mp_fillColor;

	float m_edgeThickness;

public:
	DrawStyle();
	~DrawStyle();
};