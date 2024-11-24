#pragma once
#include "Widgets/Frame.h"
#include <vector>

class GUI_API Layout : public Frame {

protected:
	std::vector<Frame*> m_frames;
	std::vector<float> m_weights;

private:
	Frame* m_mouseHoverFrame;

	GeometryResource* mp_backgroundResource;

public:
	Layout(Window* p_parent);
	~Layout();

	void onPaint() override;
	void onTick(float deltaTime) override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseDown(bool doubleClk, Math::Point2D point) override;
	void onMouseRelease(Math::Point2D point) override;
	void onMouseScroll(bool up, bool shift, bool ctr) override;

	void onKeyDown(Key key);
	void onKeyDown(char key);

	void addFrame(Frame* p_frame, float weight = 1.0f);
	void removeFrame(Frame* p_frame);
};