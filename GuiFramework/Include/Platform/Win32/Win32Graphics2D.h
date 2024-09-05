#pragma once
#include "Core/IGraphics2D.h"

class GUI_API Win32Graphics2D : public IGraphics2D {
private:
	HWND m_hWnd;

protected:
	ID2D1Factory* mp2DFactory;
	IDWriteFactory* mpWriteFactory;

	ID2D1HwndRenderTarget* mpRenderTarget;

public:
	Win32Graphics2D(HWND hWnd);
	~Win32Graphics2D();

private:
	void createGraphicsResources();
	void initGraphicsResources();

	void discardGraphicsResources();

public:
	void drawLine(Math::Point2D& x, Math::Point2D& y, DrawStyle& style);
	void drawRectangle(Math::Rect& rect, DrawStyle& style);

	void drawText(std::wstring text /*, needs a text style */);
};