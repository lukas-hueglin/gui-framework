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

	void createGraphicsAssets();
	void discardGraphicsAssets();

	void resizeCanvas();

private:
	void initGraphicsAssets();

	ID2D1HwndRenderTarget* getRenderTarget();
	IDWriteFactory* getWriteFactory();

	// make geometry and text resource a friend
	friend class Win32GeometryResource;
	friend class Win32TextResource;
};