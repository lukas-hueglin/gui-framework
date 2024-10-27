#pragma once
#include "Widgets/Label.h"

class GUI_API Button : public Label {

private:
	void (*mp_func)();

	GeometryResource* mp_rectangleResource;

public:
	Button(Window* p_parent, std::wstring text);
	~Button();

	void onPaint() override;
	void onMouseRelease(Math::Point2D point) override;

	void connect(void (*func)());

};