#include "Gui.h"
#include "Widgets/Layout.h"

Layout::Layout(Window<Graphics2D>* p_parent) : Frame(p_parent), m_mouseHoverFrame(nullptr) {
	
	// override FillMode to Expand
	m_fillMode = FillMode::Expand;

	// override alignment to TopLeft
	m_alignment = Alignment::TopLeft;
}

void Layout::onPaint() {

#ifdef DEBUG_UI
	Frame::onPaint();
#endif

	// iterate over all frames
	for (Frame* w : m_frames) {
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

void Layout::onMouseDown() {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseDown();
	}
}

void Layout::onMouseRelease() {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseRelease();
	}
}

void Layout::addFrame(Frame* p_frame, float weight) {

	m_frames.push_back(p_frame);
	m_weights.push_back(weight);

	// resize layout
	onResize(m_usedRect);
}

void Layout::removeFrame(Frame* p_frame) {

	// find index
	int index = std::distance(m_frames.begin(), std::find(m_frames.begin(), m_frames.end(), p_frame));

	m_frames.erase(m_frames.begin() + index);
	m_weights.erase(m_weights.begin() + index);
}
