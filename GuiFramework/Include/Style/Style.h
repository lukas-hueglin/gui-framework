#pragma once
#include "DrawStyle.h"
#include "TextStyle.h"

class Style {

public:
	Style() = delete;

public:
	static DrawStyle Primary();
	static DrawStyle Secondary();

	static DrawStyle Accent();
	static DrawStyle Highlight();

	static DrawStyle Cursor();
	static DrawStyle TextSelection();
	static DrawStyle Slider();

#ifdef DEBUG_UI
	static DrawStyle Debug1();
	static DrawStyle Debug2();
	static DrawStyle Debug3();
#endif

	static TextStyle Normal();
};