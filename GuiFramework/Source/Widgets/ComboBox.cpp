#include "Gui.h"
#include "Widgets/ComboBox.h"
#include "Widgets/DropDown.h"

ComboBox::ComboBox(Window* p_parent, std::vector<std::wstring> elements) : Button(p_parent, elements.at(0)), m_active(0), m_elements(elements) {

	connect(this, -1);
}

void ComboBox::onSignalReceived(int id) {

	// negative ids mean the button was pressed
	if (id < 0) {

		// create drop down
		DropDown* p_dropDown = new DropDown(mp_parent, this, Math::Point2D(Frame::m_hitboxRect.left(), Frame::m_hitboxRect.bottom()), m_elements);

		// register dropdown
		mp_parent->registerDropDown(p_dropDown);
	}

	// positive ids are the answers
	else if (id < m_elements.size()) {
		m_active = id;
		m_text = m_elements.at(id);
		mp_textResource->setText(m_text);

		requestRedraw();
		mp_parent->unregisterDropDown();
	}
}