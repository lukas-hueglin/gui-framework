#pragma once
#include "Gui.h"
#include "Style/Color.h"

class GUI_API IDrawStyle {
	
private:
	Color* mp_edgeColor;
	Color* mp_fillColor;

	float m_edgeThickness;

public:
	IDrawStyle();
	~IDrawStyle();
};