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
			AudioPlay(U"Button");
			CardsReset(getData().cards);
			changeScene(State::Title, getData().changeSec);
		}

		if (ExitCancel.leftClicked())
		{
			AudioPlay(U"Button");
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
				AudioPlay(U"Button");
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

				AudioAsset(U"Button").setVolume(getData().SoundVolume);
				AudioAsset(U"Cancel").setVolume(getData().SoundVolume);
				AudioAsset(U"Flip").setVolume(getData().SoundVolume);
				AudioAsset(U"Coin").setVolume(getData().SoundVolume);
				AudioPlay(U"Button");
			}
		}

		if (CancelButton.leftClicked())
		{
			AudioPlay(U"Cancel");
			getData().ConfigFlg = false;
			if (getData().NowScene == U"Title")
			{
				changeScene(State::Title, getData().changeSec);
			}
			else if (getData().NowScene == U"Memory")
			{
				changeScene(State::Memory, getData().changeSec);
			}
			
		}
		else if (SoundTestButton.leftClicked())
		{
			AudioPlay(U"Button");
		}
		else if (RuleButton.leftClicked())
		{
			AudioPlay(U"Button");
			getData().ConfigFlg = true;
			changeScene(State::Rule, getData().changeSec);
		}
		else if (ToExitButton.leftClicked())
		{
			AudioPlay(U"Button");
			ExitMenu = true;
		}
	}
}

//描画関数
void Config::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	//外枠
	Frame.draw(Palette::White);
	Frame.drawFrame(3, 3, Palette::Black);

	if (ExitMenu)
	{
		//「タイトルに戻りますか？」画面
		FontAsset(U"Text")(U"タイトルに戻りますか？").drawAt(800, 500, Palette::Black);
		Button(ExitButton, FontAsset(U"Button"), U"戻る", Palette::Black);
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

