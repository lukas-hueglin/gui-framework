#include "Gui.h"
#include "Core/ITextResource.h"
#include "Style/Style.h"

ITextResource::ITextResource(Graphics2D* p_graphics, TextStyle style) : mp_graphics(p_graphics), m_style(style) { }
