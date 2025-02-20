#pragma once

//ボタン類
//enable(そのボタンが押せるか)は基本true

//普通のボタン
void Button(const Rect& rect, const Font& font, const String& text, ColorF color, const bool enabled = true);

//三角形のボタン(チップ枚数選択時に使用)
//こっちは消していいかも(ベット画面実装時に考える)
void TriangleButton(const Triangle& tri, const bool enabled = true);
