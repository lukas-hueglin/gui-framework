#include "Gui.h"
#include "Style/DrawStyle.h"
#include "Style/DrawStyleBuilder.h"

DrawStyle::DrawStyle() : m_edgeColor(Color::Transparent), m_fillColor(Color::Transparent), m_edgeThickness(1.0f) { }

DrawStyle::~DrawStyle() {}

DrawStyleBuilder DrawStyle::create() {

	DrawStyle s;
	return DrawStyleBuilder(s);
}

Color& DrawStyle::getEdgeColor() {
	return m_edgeColor;
}

Color& DrawStyle::getFillColor() {
	return m_fillColor;
}

float DrawStyle::getEdgeThickness() {
	return m_edgeThickness;
}
