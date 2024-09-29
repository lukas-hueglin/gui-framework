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

	static TextStyle Normal();
};