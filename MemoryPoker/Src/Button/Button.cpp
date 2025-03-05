#include "Button.hpp"
//ボタン類
//enable(そのボタンが押せるか)は基本true

//普通のボタン(描画するだけ)
void Button(const Rect& rect, const Font& font, const String& text, const ColorF color, const bool enabled)
{
	if (enabled)
	{
		rect.draw(color);
		font(text).drawAt((rect.x + rect.w / 2), (rect.y + rect.h / 2), Palette::White);
	}
	else
	{
		rect.draw(ColorF{ 0.5 });
		font(text).drawAt((rect.x + rect.w / 2), (rect.y + rect.h / 2), Palette::White);
	}
}

//三角形のボタン(チップ枚数選択時に使用)
//こっちは消していいかも(ベット画面実装時に考える)
void TriangleButton(const Triangle& tri, const bool enabled)
{
	if (enabled)
	{
		tri.draw(Palette::Black);
	}
	else
	{
		tri.draw(ColorF{ 0.5 });
	}
}
