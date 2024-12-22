#include "Gui.h"
#include "Style/Style.h"
#include "Style/WidgetStyleBuilder.h"
#include "Style/Palette.h"


WidgetStyle Style::Default() {

	return WidgetStyle::create()
		.edgeColor(Palette::Widget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::Widget(), WidgetState::Normal)
		.fillColor(Palette::Widget().lighten(1.5f), WidgetState::Hover)
		.fillColor(Palette::Widget().lighten(1.3f), WidgetState::Click)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.lineStyle(LineStyle::Solid)
		.radius(7.0f)
		.textAlignment(Alignment::CenterLeft)
		.textColor(Palette::Text());
}

WidgetStyle Style::Layout()
{
	return WidgetStyle::create()
		.edgeColor(Palette::Widget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::Background(), WidgetState::Normal)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.lineStyle(LineStyle::Solid)
		.radius(7.0f)
		.textAlignment(Alignment::CenterLeft)
		.textColor(Palette::Text());
}

WidgetStyle Style::Slider() {
	return WidgetStyle::create()
		.edgeColor(Palette::Widget().lighten(1.2f))
		.edgeThickness(1.0f)
		.fillColor(Palette::Widget(), WidgetState::Normal)
		.fillColor(Palette::Widget().lighten(1.5f), WidgetState::Hover)
		.fillColor(Palette::Widget().lighten(1.3f), WidgetState::Click)
		.fontName(L"SegoeUI")
		.fontSize(12)
		.highlightColor(Palette::Highlight(), WidgetState::Normal)
		.highlightColor(Palette::Highlight().lighten(1.5f), WidgetState::Hover)
		.highlightColor(Palette::Highlight().lighten(1.3f), WidgetState::Click)
		.lineStyle(LineStyle::Solid)
		.radius(7.0f)
		.textAlignment(Alignment::CenterRight)
		.textColor(Palette::Text());
}
