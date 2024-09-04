#include "Gui.h"
#include "Style/IDrawStyle.h"

IDrawStyle::IDrawStyle() : mp_edgeColor(nullptr), mp_fillColor(nullptr), m_edgeThickness(1.0f) { }

IDrawStyle::~IDrawStyle() {

	if (mp_edgeColor != nullptr) {
		delete mp_edgeColor;
	}
	if (mp_fillColor != nullptr) {
		delete mp_fillColor;
	}
}
