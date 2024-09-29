#pragma once
#include "Core/IGraphics2D.h"

class GUI_API Win32Graphics2D : public IGraphics2D {
private:
	HWND m_hWnd;

protected:
	ID2D1Factory* mp_2DFactory;
	IDWriteFactory* mp_writeFactory;

	ID2D1HwndRenderTarget* mp_renderTarget;

	PAINTSTRUCT m_ps;

public:
	Win32Graphics2D(HWND hWnd);
	~Win32Graphics2D();

public:
	void beginPaint();
	void endPaint();

	void createGraphicsResources();
	void discardGraphicsResources();

	void resizeCanvas();

	void drawLine(Math::Point2D& x, Math::Point2D& y, DrawStyle style);
	void drawRectangle(Math::Rect& rect, DrawStyle style);

	void drawText(std::wstring text /*, needs a text style */);

private:
	void initGraphicsResources();
};