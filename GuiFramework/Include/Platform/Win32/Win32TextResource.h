#include "Core/ITextResource.h"
#include "Style/TextStyle.h"

class GUI_API Win32TextResource : public ITextResource {

private:
	ID2D1SolidColorBrush* mp_brush;
	IDWriteTextFormat* mp_textFormat;

public:
	Win32TextResource(Graphics2D* p_graphics, TextStyle style);
	~Win32TextResource();

private:
	void initGraphicsAssets();

public:
	void drawText(const wchar_t* text, Math::Rect& rect, Alignment textAlignment);

	void setStyle(TextStyle style);

	// make Win32Graphics2D a friend
	friend class Win32Graphics2D;
};