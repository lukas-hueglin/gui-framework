#include "Gui.h"
#include "Style/DrawStyle.h"

DrawStyle::DrawStyle() : mp_edgeColor(nullptr), mp_fillColor(nullptr), m_edgeThickness(1.0f) { }

DrawStyle::~DrawStyle() {

	if (mp_edgeColor != nullptr) {
		delete mp_edgeColor;
	}
	if (mp_fillColor != nullptr) {
		delete mp_fillColor;
	}
}
