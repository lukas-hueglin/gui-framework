#pragma once
#include "Gui.h"

template<class GRAPHICS_TYPE>
class GUI_API IWindow : public GRAPHICS_TYPE {

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