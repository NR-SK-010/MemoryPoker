#include "Memory.hpp"
#include "Button.hpp"

//神経衰弱画面

//コンストラクタ
Memory::Memory(const InitData& init)
	: IScene{ init } { }

//更新関数
void Memory::update()
{
	if (MenuButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (MenuButton.leftClicked())
	{
		AudioPlay(U"Button");
		getData().NowScene = U"Memory";
		changeScene(State::Config, getData().changeSec);
	}
}

//描画関数
void Memory::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	//メニュー(設定)ボタン
	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);

	//Player側情報表示
	PlayerCardsFrame.draw(Palette::White);
	PlayerCardsFrame.drawFrame(2, 2, Palette::Black);

	PlayerNameFrame.draw(Palette::White);
	PlayerNameFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"Player").drawAt(1250, 995, Palette::Black);

	PlayerChipFrame.draw(Palette::White);
	PlayerChipFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"CHIP").drawAt(1250, 1100, Palette::Black);



	//CPU側情報表示
	CpuCardsFrame.draw(Palette::White);
	CpuCardsFrame.drawFrame(2, 2, Palette::Black);

	CpuNameFrame.draw(Palette::White);
	CpuNameFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"CPU").drawAt(150, 90, Palette::Black);

	CpuChipFrame.draw(Palette::White);
	CpuChipFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"CHIP").drawAt(150, 195, Palette::Black);


	//場に残っているカードの描画
	for (int i : step(13 * 4))
	{
		//カードの座標
		const Vec2 center{ 260 + i % 13 * 90, 405 + (i / 13) * 130 };

		//カード描画
		getData().pack(getData().cards[i]).drawAt(center);
	}
}
