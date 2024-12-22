#include "Gui.h"
#include "Widgets/LinearLayout.h"

LinearLayout::LinearLayout(Window* p_parent, Orientation orientation) : Layout(p_parent), m_orientation(orientation) { }

void LinearLayout::onResize(Math::Rect availableRect) {

	// call parent function
	Layout::onResize(availableRect);

	// calculate the sum of all weights
	float sumExpandWeights = 0;

	for (int i = 0; i < m_frames.size(); ++i) {

		if (m_frames.at(i)->getFillMode() == FillMode::Expand) {
			sumExpandWeights += m_weights.at(i);
		}
	}

	// iterate over all frames again and set their available space
	Math::Rect minRect(availableRect.getCenter().x() - m_minSize.width() / 2, availableRect.getCenter().x() + m_minSize.width() / 2,
		availableRect.getCenter().y() - m_minSize.height() / 2, availableRect.getCenter().y() + m_minSize.height() / 2);

	Math::Rect avRect = Math::maxRect(availableRect, minRect);

	// calculate space required for shrink widgets and space left for expanding widgets
	float spaceLeft = availableRect.getSize()[m_orientation] - m_minSize[m_orientation];

	// calculate integral sizes
	float expandSpan;
	float frameSpan;

	// check if expanding widgets are present
	if (sumExpandWeights == 0) {

		// if not align the content
		avRect.topLeft()[m_orientation] += spaceLeft / 2 * (int)getJustification(m_alignment, m_orientation);
	}
	else {

		// if there are calculate the size of each one.
		expandSpan = spaceLeft / sumExpandWeights;
	}

	// iterate over all frames and set their sizes
	for (int i = 0; i < m_frames.size(); ++i) {

		if (m_frames.at(i)->getFillMode() == FillMode::Expand)
			 frameSpan = expandSpan * m_weights.at(i);
		else
			frameSpan =  m_frames.at(i)->getMinSize()[m_orientation];

		// resize avRect
		avRect.bottomRight()[m_orientation] = avRect.topLeft()[m_orientation] + frameSpan;

		// resize frame
		m_frames.at(i)->onResize(avRect);

		// set left for next one
		avRect.topLeft()[m_orientation] = avRect.bottomRight()[m_orientation];
	}
	
}

void LinearLayout::calcMinSize() {

	float width = 0.0f;
	float height = 0.0f;

	if (m_orientation == Orientation::Horizontal) {

		for (int i = 0; i < m_frames.size(); ++i) {

			width += m_frames.at(i)->getMinSize().width();
			height = max(height, m_frames.at(i)->getMinSize().height());
		}
	}
	else {

		for (int i = 0; i < m_frames.size(); ++i) {

			width = max(width, m_frames.at(i)->getMinSize().width());
			height += m_frames.at(i)->getMinSize().height();
		}
	}

	m_minSize = Math::Size(width, height);
}
