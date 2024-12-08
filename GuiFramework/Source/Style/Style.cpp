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

DrawStyle Style::Slider() {

	RGBColor fillColor = Color::DarkViolet;
	fillColor.a = 0.5;

	return DrawStyle::create()
		.edgeColor(Color::DarkOrchid)
		.fillColor(fillColor)
		.edgeThickness(1.0f);
}

DrawStyle Style::AxisLine() {

	return DrawStyle::create()
		.edgeColor(Color::Black)
		.fillColor(Color::Black)
		.edgeThickness(1.0f);
}

DrawStyle Style::AxisLineDashed() {

	return DrawStyle::create()
		.edgeColor(Color::Black)
		.fillColor(Color::Transparent)
		.lineStyle(LineStyle::Dashed)
		.edgeThickness(1.0f);
}

DrawStyle Style::Plot3(int index) {

	DrawStyleBuilder builder = DrawStyle::create()
		.fillColor(Color::Transparent)
		.lineStyle(LineStyle::Dashed)
		.edgeThickness(2.0f);

	switch (index) {

	case 0:
		builder.edgeColor(Color::Red);
		break;
	case 1:
		builder.edgeColor(Color::Blue);
		break;
	case 2:
		builder.edgeColor(Color::Green);
		break;
	default:
		builder.edgeColor(Color::Black);
	}

	return builder;
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
