#include "Gui.h"
#include "Functional.h"
#include "Common/Reflection/Internal.h"

Functional::Functional() : m_intElement(0), m_floatElement(0.0f), m_stringElement("") {
	
	// add members to reflection
	ADD_FIELD(int, m_intElement)
	ADD_FIELD(float, m_floatElement)
	ADD_FIELD(std::string, m_stringElement)
}
