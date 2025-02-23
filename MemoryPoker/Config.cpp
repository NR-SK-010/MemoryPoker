#include "Config.hpp"
#include "Button.hpp"

//コンストラクタ
//メンバ初期化リストを使用
Config::Config(const InitData& init)
	: IScene{ init } { }

//更新関数
void Config::update()
{
	if (ExitMenu)
	{
		//「タイトルに戻りますか？」画面
		if (ExitButton.mouseOver() || ExitCancel.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (ExitButton.leftClicked())
		{
			changeScene(State::Title);
		}

		if (ExitCancel.leftClicked())
		{
			AudioPlay(U"button");
			ExitMenu = false;
		}
	}
	else
	{
		if (CancelButton.mouseOver() || SoundTestButton.mouseOver() || RuleButton.mouseOver() || ToExitButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		for (int i = 0; i < BGMButtons.size(); i++)
		{
			if (BGMButtons[i].mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (BGMButtons[i].leftClicked())
			{
				if (getData().BGMVolume != 0.2 * (i + 1))
				{
					getData().BGMVolume = 0.2 * (i + 1);
				}
				else
				{
					getData().BGMVolume = 0.2 * i;
				}

				AudioAsset(U"BGM").setVolume(getData().BGMVolume);
				AudioPlay(U"button");
			}
		}

		for (int i = 0; i < SoundButtons.size(); i++)
		{
			if (SoundButtons[i].mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (SoundButtons[i].leftClicked())
			{
				if (getData().SoundVolume != 0.2 * (i + 1))
				{
					getData().SoundVolume = 0.2 * (i + 1);
				}
				else
				{
					getData().SoundVolume = 0.2 * i;
				}

				AudioAsset(U"button").setVolume(getData().SoundVolume);
				AudioAsset(U"cancel").setVolume(getData().SoundVolume);
				AudioAsset(U"flip").setVolume(getData().SoundVolume);
				AudioAsset(U"coin").setVolume(getData().SoundVolume);
				AudioPlay(U"button");
			}
		}

		if (CancelButton.leftClicked())
		{
			if (getData().NowScene == U"Title")
			{
				changeScene(State::Title, 0);
			}
			AudioPlay(U"cancel");
		}
		else if (SoundTestButton.leftClicked())
		{
			AudioPlay(U"button");
		}
		else if (RuleButton.leftClicked())
		{
			AudioPlay(U"button");
		}
		else if (ToExitButton.leftClicked())
		{
			AudioPlay(U"button");
			ExitMenu = true;
		}
	}
}

//描画関数
void Config::draw() const
{
	//外枠
	Frame.draw(Palette::White);
	Frame.drawFrame(3, 3, Palette::Black);

	if (ExitMenu)
	{
		//「タイトルに戻りますか？」画面
		FontAsset(U"Text")(U"タイトルに戻りますか？").drawAt(800, 500, Palette::Black);
		Button(ExitButton, FontAsset(U"Button"), U"終了する", Palette::Black);
		Button(ExitCancel, FontAsset(U"Button"), U"キャンセル", Palette::Black);
	}
	else
	{
		Button(CancelButton, FontAsset(U"Button"), U"✕", Palette::Black);
		Button(SoundTestButton, FontAsset{ U"Button" }, U"テスト", Palette::Black);
		Button(RuleButton, FontAsset(U"Button"), U"遊び方", Palette::Black);
		Button(ToExitButton, FontAsset(U"Button"), U"タイトルに戻る", Palette::Black);

		FontAsset(U"Text")(U"音量調整").drawAt(800, 300, Palette::Black);
		FontAsset(U"Text")(U"BGM").drawAt(650, 415, Palette::Black);
		//BGM音量調整ボタン
		for (int i = 0; i < BGMButtons.size(); i++)
		{
			Button(BGMButtons[i], FontAsset(U"Button"), U"", Palette::Skyblue, getData().BGMVolume >= 0.2 * (i + 1));
		}

		//効果音音量調整ボタン
		FontAsset(U"Text")(U"効果音").drawAt(650, 515, Palette::Black);
		for (int i = 0; i < SoundButtons.size(); i++)
		{
			Button(SoundButtons[i], FontAsset(U"Button"), U"", Palette::Skyblue, getData().SoundVolume >= 0.2 * (i + 1));
		}
	}
}
