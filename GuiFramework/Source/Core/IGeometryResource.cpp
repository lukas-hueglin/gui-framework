#include "Gui.h"
#include "Core/IGeometryResource.h"
#include "Style/Style.h"

IGeometryResource::IGeometryResource(Graphics2D* p_graphics, DrawStyle style) : mp_graphics(p_graphics), m_style(style) { }
