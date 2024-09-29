#pragma once
#include "Widgets/Label.h"

class GUI_API Button : public Label {

private:
	void (*mp_func)();

public:
	Button(Window<Graphics2D>* p_parent, const wchar_t* text);

	void onPaint() override;
	void onMouseRelease() override;

	void connect(void (*func)());

};