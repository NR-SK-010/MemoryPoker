#include <Siv3D.hpp>
#include "Button.hpp"
#include "Config.hpp"

//コンストラクタ
Config::Config(double& BGMVolume, double& SoundVolume)
{
	this->BGMVolume = BGMVolume;
	this->SoundVolume = SoundVolume;
	flg = false;
}

//更新関数
void Config::update()
{
	if (ExitMenu)
	{
		//「ゲームを終了しますか？」画面
		if (ExitButton.mouseOver() || ExitCancel.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (ExitButton.leftClicked())
		{
			System::Exit();
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
				if (BGMVolume != 0.2 * (i + 1))
				{
					BGMVolume = 0.2 * (i + 1);
				}
				else
				{
					BGMVolume = 0.2 * i;
				}

				AudioAsset(U"BGM").setVolume(BGMVolume);
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
				if (SoundVolume != 0.2 * (i + 1))
				{
					SoundVolume = 0.2 * (i + 1);
				}
				else
				{
					SoundVolume = 0.2 * i;
				}

				AudioPlay(U"button");
			}
		}

		if (CancelButton.leftClicked())
		{
			AudioPlay(U"cancel");
			flg = false;
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
		//「ゲームを終了しますか？」画面
		FontAsset(U"Text")(U"ゲームを終了しますか？").drawAt(800, 500, Palette::Black);
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
			Button(BGMButtons[i], FontAsset(U"Button"), U"", Palette::Skyblue, BGMVolume >= 0.2 * (i + 1));
		}

		//効果音音量調整ボタン
		FontAsset(U"Text")(U"効果音").drawAt(650, 515, Palette::Black);
		for (int i = 0; i < SoundButtons.size(); i++)
		{
			Button(SoundButtons[i], FontAsset(U"Button"), U"", Palette::Skyblue, SoundVolume >= 0.2 * (i + 1));
		}
	}
}

//flg用プロパティ
bool Config::getFlg() const
{
	return flg;
}

void Config::setFlg(const bool& configflg)
{
	this->flg = configflg;
}

//BGM,SoundVolumeゲッター
double Config::getBGMVolume()
{
	return BGMVolume;
}

double Config::getSoundVolume()
{
	return SoundVolume;
}
