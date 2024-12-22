#include "Widgets/Button.h"
#include <vector>

class GUI_API ComboBox : public Button {

private:
	int m_active;
	std::vector<std::wstring> m_elements;

	WidgetStyle m_style;

public:
	ComboBox(Window* p_parent, std::vector<std::wstring> elements, WidgetStyle style = Style::Default());

private:
	void onSignalReceived(int id) override;

	// make DropDown a friend class
	friend class DropDown;
};