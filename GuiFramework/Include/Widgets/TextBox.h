#pragma once
#include "Widgets/Label.h"
#include "Core/TextResource.h"

class GUI_API TextBox : public Label {

private:
	std::wstring m_backupText;

	GeometryResource* mp_rectangleResource;
	GeometryResource* mp_cursorResource;
	GeometryResource* mp_selectionResource;

	int m_firstCursor;
	int m_lastCursor;
	float m_animCycle;

	bool m_dragFirstCursor;

protected:
	bool m_edit;
	bool m_requireDoubleClk;

	std::wstring m_prefix;
	std::wstring m_suffix;


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

	void setRequireDoubleClick(bool requireDoubleClk);
	void setPrefix(std::wstring prefix);
	void setSuffix(std::wstring suffix);

protected:
	virtual bool filterInput(char key);

	virtual void enableEditMode();
	virtual void disableEditMode(bool backup);

	void updateText();

};