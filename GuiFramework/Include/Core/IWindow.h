#pragma once
#include "Gui.h"
#include "Core/Graphics2D.h"

template<class GRAPHICS_TYPE>
class GUI_API IWindow {
protected:
	GRAPHICS_TYPE* mp_graphics;

public:
	IWindow();
	~IWindow();
	
public:
	template<class DERIVED_TYPE>
	static DERIVED_TYPE* create(std::wstring title);

private:
	virtual void initialize(std::wstring title) = 0;

	// make all other templated IWindow classes a friend
	friend class IWindow;
};