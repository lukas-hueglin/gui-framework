#pragma once
#include "Widgets/Label.h"
#include "Core/TextResource.h"

class GUI_API TextBox : public Label {

private:
	std::wstring m_backupText;

	int m_firstCursor;
	int m_lastCursor;
	bool m_edit;
	bool m_dragFirstCursor;

	float m_animCycle;

	GeometryResource* mp_rectangleResource;
	GeometryResource* mp_cursorResource;
	GeometryResource* mp_selectionResource;


public:
	TextBox(Window* p_parent, std::wstring text);
	~TextBox();

	void onTick(float deltaTime) override;
	void onPaint() override;

	void onMouseLeave() override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseDown(bool doubleClk, Math::Point2D point) override;
	void onKeyDown(Key key) override;
	void onKeyDown(char key) override;

};