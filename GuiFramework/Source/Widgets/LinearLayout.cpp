#include "Gui.h"
#include "Widgets/LinearLayout.h"

LinearLayout::LinearLayout(Window<Graphics2D>* p_parent, Orientation orientation) : Layout(p_parent), m_orientation(orientation) { }

void LinearLayout::onResize(Math::Rect availableRect) {

	// call parent function
	Layout::onResize(availableRect);

	// iterate over all frames and get the sum of all the shrinking frames sizes
	Math::Size sumShrinkSize = Math::Size(0.0f, 0.0f);
	float sumExpandWeights = 0;

	for (int i = 0; i < m_frames.size(); ++i) {
		
		if (m_frames.at(i)->getFillMode() == FillMode::Expand)
			sumExpandWeights += m_weights.at(i);
		else
			sumShrinkSize += m_frames.at(i)->getMinSize();
	}

	// iterate over all frames again and set their available space
	Math::Rect avRect = m_contentRect;

	// calculate space required for shrink widgets and space left for expanding widgets
	float shrinkSpan = sumShrinkSize[m_orientation];
	float spaceLeft = avRect.getSize()[m_orientation] - shrinkSpan;

	// calculate integral sizes
	float expandSpan;
	float frameSpan;

	// check if expanding widgets are present
	if (sumExpandWeights == 0) {
		// if not align the content
		avRect.left() += spaceLeft / 2 * (int) getJustification(m_alignment, m_orientation);
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
