#pragma once
#include "Widgets/Widget.h"
#include "Core/TextResource.h"

class GUI_API Label : public Widget {

private:
	const wchar_t* m_text;

	Alignment m_textAlignment;

	TextResource* mp_textResource;

public:
	Label(Window* p_parent, const wchar_t* text);
	~Label();

	void onPaint() override;

};