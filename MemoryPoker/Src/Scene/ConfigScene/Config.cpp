﻿#include "Config.hpp"
#include "../../Button/Button.hpp"

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
			AudioPlay(U"Button", getData().SoundVolume);

			//カード情報リセット
			CardsReset(getData().cards);
			getData().UsedCards.clear();

			//Player,CPU情報リセット
			getData().player.AllClear();
			getData().cpu.AllClear();

			//Betシーンのフラグリセット
			getData().RaiseMenu = false;

			//ラウンドリセット
			getData().Round = 1;

			changeScene(State::Title, getData().changeSec);
		}

		if (ExitCancel.leftClicked())
		{
			AudioPlay(U"Button", getData().SoundVolume);
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
				if (getData().BGMVolume != volumeLevels[i+1])
				{
					getData().BGMVolume = volumeLevels[i+1];
				}
				else
				{
					getData().BGMVolume = volumeLevels[i];
				}

				AudioAsset(U"BGM").setVolume(getData().BGMVolume);
				AudioPlay(U"Button", getData().SoundVolume);
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
				if (getData().SoundVolume != volumeLevels[i+1])
				{
					getData().SoundVolume = volumeLevels[i+1];
				}
				else
				{
					getData().SoundVolume = volumeLevels[i];
				}

				AudioAsset(U"Button").setVolume(getData().SoundVolume);
				AudioAsset(U"Cancel").setVolume(getData().SoundVolume);
				AudioAsset(U"Flip").setVolume(getData().SoundVolume);
				AudioAsset(U"Coin").setVolume(getData().SoundVolume);
				AudioPlay(U"Button", getData().SoundVolume);
			}
		}

		if (CancelButton.leftClicked())
		{
			AudioPlay(U"Cancel", getData().SoundVolume);
			getData().ConfigFlg = false;
			if (getData().NowScene == U"Title")
			{
				changeScene(State::Title, getData().changeSec);
			}
			else if (getData().NowScene == U"Memory")
			{
				//ストップウォッチ再開
				getData().stopwatch.resume();

				changeScene(State::Memory, getData().changeSec);
			}
			else if (getData().NowScene == U"SelectCard")
			{
				changeScene(State::SelectCard, getData().changeSec);
			}
			else if (getData().NowScene == U"Bet")
			{
				changeScene(State::Bet, getData().changeSec);
			}
			else if (getData().NowScene == U"ShowDown")
			{
				//ストップウォッチ再開
				getData().stopwatch.resume();

				changeScene(State::ShowDown, getData().changeSec);
			}
			else if (getData().NowScene == U"Result")
			{
				changeScene(State::Result, getData().changeSec);
			}
			
		}
		else if (SoundTestButton.leftClicked())
		{
			//ランダムに効果音のどれかを再生
			double rand = Random<double>(0.0, 1.0);
			if (rand < 0.25)
			{
				AudioPlay(U"Button", getData().SoundVolume);
			}
			else if (rand < 0.50)
			{
				AudioPlay(U"Cancel", getData().SoundVolume);
			}
			else if (rand < 0.75)
			{
				AudioPlay(U"Flip", getData().SoundVolume);
			}
			else
			{
				AudioPlay(U"Coin", getData().SoundVolume);
			}
			
		}
		else if (RuleButton.leftClicked())
		{
			AudioPlay(U"Button", getData().SoundVolume);
			getData().ConfigFlg = true;
			changeScene(State::Rule, getData().changeSec);
		}
		else if (ToExitButton.leftClicked())
		{
			AudioPlay(U"Button", getData().SoundVolume);
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
			Button(BGMButtons[i], FontAsset(U"Button"), U"", Palette::Skyblue, getData().BGMVolume >= volumeLevels[i + 1]);
		}

		//効果音音量調整ボタン
		FontAsset(U"Text")(U"効果音").drawAt(650, 515, Palette::Black);
		for (int i = 0; i < SoundButtons.size(); i++)
		{
			Button(SoundButtons[i], FontAsset(U"Button"), U"", Palette::Skyblue, getData().SoundVolume >= volumeLevels[i + 1]);
		}
	}
}

