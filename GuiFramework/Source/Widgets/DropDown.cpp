#include "Gui.h"
#include "Widgets/DropDown.h"
#include "Widgets/Button.h"

DropDown::DropDown(Window* p_parent, Frame* p_client, Math::Point2D origin, std::vector<std::wstring> elements) : LinearLayout(p_parent, Orientation::Vertical), mp_client(p_client) {

	// resize frame
	Math::Point2D bottomRight = origin + Math::Point2D(150, elements.size() * 50);
	onResize(Math::Rect(origin, bottomRight));

	// add all elements to the layout
	for (int i = 0; i < elements.size(); ++i) {

		// create button
		Button* b = new Button(p_parent, elements.at(i));
		b->connect(p_client, i);

		// add button
		addFrame(b);
	}
}

DropDown::~DropDown() {

	// delete all buttons
	for (Frame* frame : m_frames) {
		delete frame;
	}
}
