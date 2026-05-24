#include "Gui.h"
#include "Widgets/Layout.h"
#include "Style/Style.h"

Layout::Layout(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, WidgetStyle style):
	Widget2d(creds, p_app, p_window, p_parent, style), m_mouseHoverWidget(nullptr) {
	
	// override FillMode to Expand
	m_fillMode = FillMode::Expand;

	// override immediate mode
	enableImmediateMode();

	// override draw background
	setDrawBackground(true);
}

void Layout::onResize(Math::Rect availableRect) {

	// calculate minimal size
	calcMinSize();

	// call parent function
	Widget2d::onResize(availableRect);
}

void Layout::onMouseEnter() {}

void Layout::onMouseLeave() {

	// make sure mouse left child widget
	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onMouseLeave();
		m_mouseHoverWidget = nullptr;
	}
}

void Layout::onMouseDown(bool doubleClk, Math::Point2D point) {

	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onMouseDown(doubleClk, point);
	}
}

void Layout::onMouseRelease(Math::Point2D point) {

	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onMouseRelease(point);
	}
}

void Layout::onMouseScroll(bool up, bool shift, bool ctr) {

	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onMouseScroll(up, shift, ctr);
	}
}

void Layout::onKeyDown(Key key) {

	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onKeyDown(key);
	}
}

void Layout::onKeyDown(char key) {

	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onKeyDown(key);
	}
}

Math::Size Layout::getMinSize() {

	calcMinSize();
	return m_minSize;
}
