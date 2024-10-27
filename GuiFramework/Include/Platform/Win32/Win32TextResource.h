#include "Core/ITextResource.h"
#include "Style/TextStyle.h"

class GUI_API Win32TextResource : public ITextResource {

private:
	ID2D1SolidColorBrush* mp_brush;
	IDWriteTextFormat* mp_textFormat;
	IDWriteTextLayout* mp_textLayout;

public:
	Win32TextResource(Graphics2D* p_graphics, TextStyle style);
	~Win32TextResource();

private:
	void initGraphicsAssets();
	void updateGraphicsAssets();

public:
	void drawText(std::wstring text, Math::Rect& rect, Alignment textAlignment) override;
	void drawText(std::wstring text) override;
	void drawText() override;

	void setText(std::wstring text) override;
	void setRect(Math::Rect& rect) override;
	void setTextAlignment(Alignment textAlignment) override;

	int getMousePosition(Math::Point2D point);
	Math::Rect getCursorPosition(int cursor, bool trailing = false) override;

	// make Win32Graphics2D a friend
	friend class Win32Graphics2D;
};