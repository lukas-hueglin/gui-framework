#pragma once
#include "Widgets/Label.h"

class GUI_API Button : public Label {

protected:
	Object* mp_client;
	int m_id;

	GeometryResource* mp_rectangleResource;

public:
	Button(Window* p_parent, std::wstring text);
	~Button();

	void onPaint() override;
	void onMouseRelease(Math::Point2D point) override;

	void connect(Object* p_client, int id);
};