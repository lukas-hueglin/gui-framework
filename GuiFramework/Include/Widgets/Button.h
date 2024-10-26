#pragma once
#include "Widgets/Label.h"

class GUI_API Button : public Label {

private:
	void (*mp_func)();

	GeometryResource* mp_rectangleResource;

public:
	Button(Window* p_parent, const wchar_t* text);
	~Button();

	void onPaint() override;
	void onMouseRelease() override;

	void connect(void (*func)());

};