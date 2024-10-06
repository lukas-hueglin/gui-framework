#pragma once
#include "Widgets/Frame.h"
#include <vector>

class GUI_API Layout : public Frame {

protected:
	std::vector<Frame*> m_frames;
	std::vector<float> m_weights;

private:
	Frame* m_mouseHoverFrame;

public:
	Layout(Window<Graphics2D>* p_parent);

	void onPaint() override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseDown() override;
	void onMouseRelease() override;

	void addFrame(Frame* p_frame, float weight = 1.0f);
	void removeFrame(Frame* p_frame);
};