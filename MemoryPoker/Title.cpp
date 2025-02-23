#include "Title.hpp"
#include "Button.hpp"

//タイトル画面

//コンストラクタ
//メンバ初期化リストを使用
Title::Title(const InitData& init)
	: IScene{ init } { }

//毎フレーム update() -> draw()の順で呼ばれる

//更新関数
void Title::update()
{
	if (startButton.mouseOver() || ruleButton.mouseOver() || configButton.mouseOver() || exitButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (startButton.leftClicked())
	{
		AudioPlay(U"button");
		//ゲーム画面(Memory)へ
	}
	else if (ruleButton.leftClicked())
	{
		AudioPlay(U"button");
		//ルール説明へ
	}
	else if (configButton.leftClicked())
	{
		AudioPlay(U"button");
		//設定画面へ
		getData().NowScene = U"Title";
		changeScene(State::Config, 0);
	}
	else if (exitButton.leftClicked())
	{
		AudioPlay(U"button");
		//終了
		System::Exit();
	}
}

//描画関数
void Title::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	//タイトル表示
	FontAsset(U"Title")(U"神経衰弱ポーカー").drawAt(TextStyle::Outline(10, ColorF{ 0 }), 800, 300);

	//ボタン表示
	Button(startButton, FontAsset(U"Button"), U"スタート", Palette::Black);
	Button(ruleButton, FontAsset(U"Button"), U"遊び方", Palette::Black);
	Button(configButton, FontAsset(U"Button"), U"設定", Palette::Black);
	Button(exitButton, FontAsset(U"Button"), U"終了する", Palette::Black);


}
