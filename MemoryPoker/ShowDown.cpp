#include "ShowDown.hpp"
#include "Button.hpp"

//コンストラクタ
ShowDown::ShowDown(const InitData& init)
	: IScene{ init } {
}

//更新関数
void ShowDown::update()
{
	if (MenuButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (MenuButton.leftClicked())
	{
		AudioPlay(U"Button");
		getData().NowScene = U"ShowDown";
		changeScene(State::Config, getData().changeSec);
	}

}

//描画関数
void ShowDown::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);
}
