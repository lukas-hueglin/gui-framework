#pragma once
#include "Core/IFunctional.h"

#include <string>

class Functional : public IFunctional {

private:
	int m_intElement;
	float m_floatElement;
	std::string m_stringElement;

public:
	Functional();

	IMPLEMENT_LOADSAVE(Functional);
};