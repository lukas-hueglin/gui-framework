#include "Gui.h"
#include "Widgets/LinearLayout.h"

LinearLayout::LinearLayout(Window<Graphics2D>* p_parent, Orientation orientation) : Layout(p_parent), m_orientation(orientation) { }

void LinearLayout::onResize(Math::Rect availableRect) {

	// call parent function
	Layout::onResize(availableRect);

	// iterate over all frames and get shrink size
	Math::Size sumSize = Math::Size(0, 0);
	float sumWeights = 0;

	for (int i = 0; i < m_frames.size(); ++i) {
		
		if (m_frames.at(i)->getFillMode() == FillMode::Expand) {

			sumWeights += m_weights.at(i);
		}
		else {

			sumSize = sumSize + m_frames.at(i)->getMinSize();
		}
	}

	// iterate over all frames again and set their available space
	Math::Rect available = m_contentRect;

	// check if horizontal or vertical orientation is set
	if (m_orientation == Orientation::Horizontal) {

		// calculate integral sizes
		float expandWidth = 1;

		if (sumWeights == 0) {
			available.left += (available.getWidth() - sumSize.width) / 2 * (m_alignment % 3);
		}
		else {
			expandWidth = (available.getWidth() - sumSize.width) / sumWeights;
		}

		for (int i = 0; i < m_frames.size(); ++i) {

			if (m_frames.at(i)->getFillMode() == FillMode::Expand) {

				available.right = available.left + expandWidth * m_weights.at(i);
			}
			else {

				available.right = available.left + m_frames.at(i)->getMinSize().width;
			}

			// resize frame
			m_frames.at(i)->onResize(available);

			// set left for next one
			available.left = available.right;
		}
	}
	else {
		// calculate integral sizes
		float expandHeight = 1;

		if (sumWeights == 0) {
			available.top += (available.getHeight() - sumSize.height) / 2 * (m_alignment / 2);
		}
		else {
			expandHeight = (available.getHeight() - sumSize.height) / sumWeights;
		}

		for (int i = 0; i < m_frames.size(); ++i) {

			if (m_frames.at(i)->getFillMode() == FillMode::Expand) {

				available.bottom = available.top + expandHeight * m_weights.at(i);
			}
			else {

				available.bottom = available.top + m_frames.at(i)->getMinSize().height;
			}

			// resize frame
			m_frames.at(i)->onResize(available);

			// set top for next one
			available.top = available.bottom;
		}
	}
	
}
