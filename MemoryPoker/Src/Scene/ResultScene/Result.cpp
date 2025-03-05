#include "Result.hpp"
#include "../../Button/Button.hpp"

//神経衰弱画面

//コンストラクタ
Result::Result(const InitData& init)
	: IScene{ init } {
}

//更新関数
void Result::update()
{
	if (MenuButton.mouseOver() || TitleButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (MenuButton.leftClicked())
	{
		AudioPlay(U"Button", getData().SoundVolume);
		getData().NowScene = U"Result";

		//設定画面を開くときは一時停止
		getData().stopwatch.pause();

		changeScene(State::Config, getData().changeSec);
	}
	else if (TitleButton.leftClicked())
	{
		AudioPlay(U"Button", getData().SoundVolume);

		changeScene(State::Title, getData().changeSec);
	}
}

//描画関数
void Result::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);
	Button(TitleButton, FontAsset(U"Button"), U"タイトル", Palette::Black);

	//結果表示
	if (getData().player.getChip() > getData().cpu.getChip())
	{
		FontAsset(U"Result")(U"PLAYER WIN").drawAt(800, 300);
	}
	else if (getData().player.getChip() == getData().cpu.getChip())
	{
		FontAsset(U"Result")(U"DRAW").drawAt(800, 300);
	}
	else
	{
		FontAsset(U"Result")(U"CPU WIN").drawAt(800, 300);
	}

	//Player情報表示
	PlayerNameArea.draw(Palette::White);
	PlayerNameArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().player.getName()).drawAt(1250, 540, Palette::Black);

	PlayerChipArea.draw(Palette::White);
	PlayerChipArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().player.getChip()).drawAt(1450, 645, Palette::Black);


	//Cpu情報表示
	CpuNameArea.draw(Palette::White);
	CpuNameArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().cpu.getName()).drawAt(150, 540, Palette::Black);

	CpuChipArea.draw(Palette::White);
	CpuChipArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().cpu.getChip()).drawAt(350, 645, Palette::Black);
}
