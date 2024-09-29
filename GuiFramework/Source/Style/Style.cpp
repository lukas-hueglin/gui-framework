#include "Gui.h"
#include "Style/Style.h"
#include "Style/DrawStyleBuilder.h"

DrawStyle Style::Primary() {

	return DrawStyle::create()
		.edgeColor(Color::Transparent)
		.fillColor(Color::DimGray)
		.edgeThickness(1.0f);
}

DrawStyle Style::Secondary() {

	return DrawStyle::create()
		.edgeColor(Color::Transparent)
		.fillColor(Color::SlateGray)
		.edgeThickness(1.0f);
}

DrawStyle Style::Accent() {

	return DrawStyle::create()
		.edgeColor(Color::MediumSlateBlue)
		.fillColor(Color::SlateBlue)
		.edgeThickness(1.0f);
}

DrawStyle Style::Highlight() {

	return DrawStyle::create()
		.edgeColor(Color::DarkOrchid)
		.fillColor(Color::DarkViolet)
		.edgeThickness(1.0f);
}