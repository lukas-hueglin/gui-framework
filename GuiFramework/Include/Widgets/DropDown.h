#include "Widgets/LinearLayout.h"

class GUI_API DropDown : public LinearLayout {

private:
	Frame* mp_client;

public:
	DropDown(Window* p_parent, Frame* p_client, Math::Point2D origin, std::vector<std::wstring> elements);

	~DropDown();
};