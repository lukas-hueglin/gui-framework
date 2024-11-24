#include "Gui.h"
#include "Widgets/Plot.h"
#include "Style/Style.h"

#include <iostream>
#include <math.h>

Plot::Plot(Window* p_parent) : Widget(p_parent), m_plotRect(Math::Rect(0.f, 0.f, 0.f, 0.f)), m_plotBounds(Math::Rect(0.f, 1.f, 1.f, 0.f)), m_lockXZoom(false), m_lockYZoom(false) {

	// create geometry and text resource
	mp_backgroundGeometryResource = new GeometryResource(mp_graphics, Style::Primary());
	mp_axisGeometryResource = new GeometryResource(mp_graphics, Style::AxisLine());
	mp_linesGeometryResource = new GeometryResource(mp_graphics, Style::AxisLineDashed());

	mp_textResource = new TextResource(mp_graphics, Style::Normal());
	mp_textResource->setTextAlignment(Alignment::Center);
}

Plot::~Plot() {

	delete mp_textResource;
	delete mp_backgroundGeometryResource;
	delete mp_axisGeometryResource;
	delete mp_linesGeometryResource;
}

void Plot::onPaint() {

	Widget::onPaint();

	// draw background
	mp_backgroundGeometryResource->drawRectangle(m_hitboxRect);

	// draw axis
	Math::Point2D origin(m_plotRect.left() - 10, m_plotRect.bottom() + 10);
	Math::Point2D x_axis(m_plotRect.right(), m_plotRect.bottom() + 10);
	Math::Point2D y_axis(m_plotRect.left() - 10, m_plotRect.top());

	mp_axisGeometryResource->drawArrow(origin, x_axis, 10.0f);
	mp_axisGeometryResource->drawArrow(origin, y_axis, 10.0f);

	// calculate spacing
	float width = m_plotBounds.getWidth();
	float height = -m_plotBounds.getHeight();

	int p_x = floor(log10(width));
	float q_x = pow(10, p_x);
	int p_y = floor(log10(height));
	float q_y = pow(10, p_y);

	// starting point
	float b_x = ceil(m_plotBounds.left() / q_x) * q_x;
	float b_y = ceil(m_plotBounds.bottom() / q_y) * q_y;

	// draw 10 lines
	for (int i = 0; i < 10; ++i) {

		// subtract the height because the refrence frame in the plot is flipped (top > bottom)
		float x = b_x + q_x * i;
		float y = b_y + q_y * i;

		DEBUG_PRINTLN(x)

		// check if line is in plot
		if (x < m_plotBounds.right()) {
			drawVerticalTicks(x);
		}
		if (y < m_plotBounds.top()) {
			drawHorizontalTicks(y);
		}
	}
}

void Plot::onResize(Math::Rect availableRect) {

	// call parent function
	Widget::onResize(availableRect);

	m_plotRect = Math::shrinkRect(m_contentRect, 60);
}

void Plot::onMouseHover(Math::Point2D point) {

	// call parent function
	Widget::onMouseHover(point);

	if (m_mouseDown) {
		Math::Point2D translation = relativeScreenToPlotSpace(m_mouseDelta);
		m_plotBounds.topLeft() += translation;
		m_plotBounds.bottomRight() += translation;

		requestRedraw();
	}
}

void Plot::onMouseScroll(bool up, bool shift, bool ctr) {

	// get zoom factor
	float zoom = up ? 1.5f : 0.666f;

	// create variables
	float left, right, top, bottom;

	// dont scale y if shift is pressed
	if (shift) {
		top = m_plotBounds.top();
		bottom = m_plotBounds.bottom();
	}
	else {
		top = (m_plotBounds.top() - m_plotBounds.getCenter().y()) * zoom + m_plotBounds.getCenter().y();
		bottom = (m_plotBounds.bottom() - m_plotBounds.getCenter().y()) * zoom + m_plotBounds.getCenter().y();
	}

	// calculate horizontal component
	left = (m_plotBounds.left() - m_plotBounds.getCenter().x()) * zoom + m_plotBounds.getCenter().x();
	right = (m_plotBounds.right() - m_plotBounds.getCenter().x()) * zoom + m_plotBounds.getCenter().x();

	m_plotBounds = Math::Rect(left, right, top, bottom);

	requestRedraw();
}

void Plot::setLockXZoom(bool lock) {

	m_lockXZoom = lock;
}

void Plot::setLockYZoom(bool lock) {

	m_lockYZoom = lock;
}

Math::Point2D Plot::plotToScreenSpace(Math::Point2D point) {

	float x = (point.x() - m_plotBounds.left()) / m_plotBounds.getWidth() * m_plotRect.getWidth() + m_plotRect.left();
	float y = (point.y() - m_plotBounds.bottom()) / m_plotBounds.getHeight() * m_plotRect.getHeight() + m_plotRect.bottom();

	return Math::Point2D(x, y);
}

Math::Point2D Plot::screenToPlotSpace(Math::Point2D point) {

	float x = (point.x() - m_plotRect.left()) / m_plotRect.getWidth() * m_plotBounds.getWidth() + m_plotBounds.left();
	float y = (point.y() - m_plotRect.bottom()) / m_plotRect.getHeight() * m_plotBounds.getHeight() + m_plotBounds.bottom();

	return Math::Point2D(x, y);
}

Math::Point2D Plot::relativeScreenToPlotSpace(Math::Point2D point) {

	float x = point.x() / m_plotRect.getWidth() * m_plotBounds.getWidth();
	float y = point.y() / m_plotRect.getHeight() * m_plotBounds.getHeight();

	return Math::Point2D(x, y);
}

void Plot::drawHorizontalTicks(float value) {

	// calculate points
	Math::Point2D lineBegin = plotToScreenSpace(Math::Point2D(m_plotBounds.left(), value));
	Math::Point2D lineEnd = plotToScreenSpace(Math::Point2D(m_plotBounds.right(), value));
	Math::Point2D tickBegin = lineBegin - Math::Point2D(15, 0);
	Math::Point2D tickEnd = lineBegin - Math::Point2D(5, 0);
	Math::Rect textRect(lineBegin.x() - 55, lineBegin.x() - 20, lineBegin.y() - 10, lineBegin.y() + 10);

	// draw dashed line
	mp_linesGeometryResource->drawLine(lineBegin, lineEnd);

	// draw tick
	mp_axisGeometryResource->drawLine(tickBegin, tickEnd);

	// convert to string
	std::wstringstream wss;
	wss << value;
	std::wstring text = wss.str();

	// draw value
	mp_textResource->drawText(text, textRect, Alignment::CenterRight);
}

void Plot::drawVerticalTicks(float value) {

	// calculate points
	Math::Point2D lineBegin = plotToScreenSpace(Math::Point2D(value, m_plotBounds.bottom()));
	Math::Point2D lineEnd = plotToScreenSpace(Math::Point2D(value, m_plotBounds.top()));
	Math::Point2D tickBegin = lineBegin + Math::Point2D(0, 15);
	Math::Point2D tickEnd = lineBegin + Math::Point2D(0, 5);
	Math::Rect textRect(lineBegin.x() - 20, lineBegin.x() + 20, lineBegin.y() + 20, lineBegin.y() + 40);

	// draw dashed line
	mp_linesGeometryResource->drawLine(lineBegin, lineEnd);

	// draw tick
	mp_axisGeometryResource->drawLine(tickBegin, tickEnd);

	// convert to string
	std::wstringstream wss;
	wss << value;
	std::wstring text = wss.str();

	// draw value
	mp_textResource->drawText(text, textRect, Alignment::TopCenter);
}