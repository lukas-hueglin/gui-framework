#pragma once
#include "Widgets/Widget.h"

class GUI_API Label : public Widget {

private:
	const wchar_t* m_text;

	Alignment m_textAlignment;

public:
	Label(Window<Graphics2D>* p_parent, const wchar_t* text);

	void onPaint() override;

};