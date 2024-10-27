#pragma once
#include "Widgets/Widget.h"
#include "Core/TextResource.h"
#include <string>

class GUI_API Label : public Widget {

protected:
	std::wstring m_text;

	Alignment m_textAlignment;

	TextResource* mp_textResource;

public:
	Label(Window* p_parent, std::wstring text);
	~Label();

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;
};