#include "Gui.h"
#include "Style/Style.h"
#include "Style/DrawStyleBuilder.h"
#include "Style/TextStyleBuilder.h"

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

DrawStyle Style::Cursor() {
	return DrawStyle::create()
		.edgeColor(Color::Black)
		.fillColor(Color::Transparent)
		.edgeThickness(1.0f);
}

DrawStyle Style::TextSelection() {

	RGBColor fillColor = Color::Blue;
	fillColor.a = 0.5;

	return DrawStyle::create()
		.edgeColor(Color::LightBlue)
		.fillColor(fillColor)
		.edgeThickness(1.0f);
}

#ifdef DEBUG_UI
DrawStyle Style::Debug1() {

	return DrawStyle::create()
		.edgeColor(Color::Red)
		.fillColor(Color::Transparent)
		.edgeThickness(1.0f);
}

DrawStyle Style::Debug2() {

	return DrawStyle::create()
		.edgeColor(Color::Green)
		.fillColor(Color::Transparent)
		.edgeThickness(1.0f);
}

DrawStyle Style::Debug3() {

	return DrawStyle::create()
		.edgeColor(Color::Blue)
		.fillColor(Color::Transparent)
		.edgeThickness(1.0f);
}
#endif


TextStyle Style::Normal() {

	return TextStyle::create()
		.textColor(Color::Black)
		.fontSize(12)
		.fontName(L"SegoeUI");
}
