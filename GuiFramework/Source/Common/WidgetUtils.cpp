#include "Gui.h"
#include "Common/WidgetUtils.h"


Justification getJustification(Alignment& alignment, Orientation& orientation) {
	return (Justification)(orientation == Orientation::Horizontal ? alignment % 3 : alignment / 3);
}