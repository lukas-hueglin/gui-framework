#include "Gui.h"
#include "Widgets/Layout.h"
#include "Style/Style.h"

Layout::Layout(Window* p_parent, WidgetStyle style) : Frame(p_parent), m_mouseHoverFrame(nullptr), m_layoutImpl(mp_graphics, style) {
	
	// override FillMode to Expand
	m_fillMode = FillMode::Expand;

	// override immediate mode
	enableImmediateMode();
}

void Layout::onPaint() {

	// paint background
	m_layoutImpl.onPaint(m_usedRect);

	// iterate over all frames
	for (Frame* w : m_frames) {
		w->onPaint();
	}

	// call parent function
	Frame::onPaint();
}

void Layout::onResize(Math::Rect availableRect) {

	// call parent function
	Frame::onResize(availableRect);

	// calculate minimal size
	calcMinSize();
}

void Layout::onTick(float deltaTime) {

	// iterate over all frames
	for (Frame* w : m_frames) {
		if (w->isImmediateMode())
			w->onTick(deltaTime);
		if (w->hasRequestedRedraw())
			w->onPaint();
	}
}

void Layout::onMouseHover(Math::Point2D point) {

	// iterate over all frames
	for (Frame* w : m_frames) {

		if (Math::pointInRect(w->getHitbox(), point)) {

			// check if mouse was already hovering
			if (w != m_mouseHoverFrame) {
				w->onMouseEnter();
				m_mouseHoverFrame = w;
			}

			w->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (w == m_mouseHoverFrame) {
			w->onMouseLeave();
			m_mouseHoverFrame = nullptr;
		}
	}
}

void Layout::onMouseEnter() {}

void Layout::onMouseLeave() {

	// make sure mouse left child frame
	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseLeave();
		m_mouseHoverFrame = nullptr;
	}
}

void Layout::onMouseDown(bool doubleClk, Math::Point2D point) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseDown(doubleClk, point);
	}
}

void Layout::onMouseRelease(Math::Point2D point) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseRelease(point);
	}
}

void Layout::onMouseScroll(bool up, bool shift, bool ctr) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseScroll(up, shift, ctr);
	}
}

void Layout::onKeyDown(Key key) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onKeyDown(key);
	}
}

void Layout::onKeyDown(char key) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onKeyDown(key);
	}
}

void Layout::addFrame(Frame* p_frame, float weight) {

	m_frames.push_back(p_frame);
	m_weights.push_back(weight);

	onResize(m_usedRect);
}

void Layout::removeFrame(Frame* p_frame) {

	// find index
	int index = std::distance(m_frames.begin(), std::find(m_frames.begin(), m_frames.end(), p_frame));

	m_frames.erase(m_frames.begin() + index);
	m_weights.erase(m_weights.begin() + index);
}
