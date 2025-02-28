#include "Bet.hpp"
#include "Button.hpp"

//コンストラクタ
Bet::Bet(const InitData& init)
	: IScene{ init } {
}

//更新関数
void Bet::update()
{
	if (MenuButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (MenuButton.leftClicked())
	{
		AudioPlay(U"Button");
		getData().NowScene = U"Bet";
		changeScene(State::Config, getData().changeSec);
	}
}

//描画関数
void Bet::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	//メニューボタン
	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);
}
