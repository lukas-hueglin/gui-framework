#include "Gui.h"
#include "Widgets/DropDown.h"
#include "Widgets/Button.h"

DropDown::DropDown(Window* p_parent, Frame* p_client, Math::Point2D origin, std::vector<std::wstring> elements, WidgetStyle style) : LinearLayout(p_parent, Orientation::Vertical), mp_client(p_client) {

	// add all elements to the layout
	for (int i = 0; i < elements.size(); ++i) {

		// create button
		Button* b = new Button(p_parent, elements.at(i), style);

		// set margin and minsize
		b->setPadding(10.0f);
		b->setMinSize(Math::Size(130, 30));

		b->connect(p_client, i);

		// add button
		addFrame(b);
	}

	// resize frame
	Math::Point2D bottomRight = origin + Math::Point2D(130, elements.size() * 30);
	onResize(Math::Rect(origin, bottomRight));
}

DropDown::~DropDown() {

	// delete all buttons
	for (Frame* frame : m_frames) {
		delete frame;
	}
}
