#pragma once
#include "Widgets/Widget2d.h"
#include "Style/Style.h"
#include <vector>

class GUI_API Layout : public Widget2d {

protected:
	Widget* m_mouseHoverWidget;

public:
	Layout(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, WidgetStyle style = Style::Layout());

	void onResize(Math::Rect availableRect) override;

	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseDown(bool doubleClk, Math::Point2D point) override;
	void onMouseRelease(Math::Point2D point) override;
	void onMouseScroll(bool up, bool shift, bool ctr) override;

	void onKeyDown(Key key);
	void onKeyDown(char key);

	Math::Size getMinSize() override;

private:
	virtual void calcMinSize() = 0;
};