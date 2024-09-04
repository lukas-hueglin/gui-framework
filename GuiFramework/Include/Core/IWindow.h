#pragma once
#include "Gui.h"

template<class GRAPHICS_TYPE>
class GUI_API IWindow : public GRAPHICS_TYPE {

private:
	IWindow();
	
public:
	template<class DERIVED_TYPE>
	static DERIVED_TYPE* create();

private:
	virtual void initialize() = 0;
};