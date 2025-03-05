#include "Title.hpp"
#include "../../Button/Button.hpp"

//タイトル画面

//コンストラクタ
//メンバ初期化リストを使用
Title::Title(const InitData& init)
	: IScene{ init } { }

//毎フレーム update() -> draw()の順で呼ばれる

//更新関数
void Title::update()
{
	if (SelectFlg)
	{
		//先攻後攻選択画面
		if (firstButton.mouseOver() || lastbutton.mouseOver() || cancelButton.mouseOver() || easyButton.mouseOver() ||
			normalButton.mouseOver() || hardButton.mouseOver() || okButton.mouseOver() )
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (firstButton.leftClicked())
		{
			//先攻
			AudioPlay(U"Button");

			//ボタン状態設定
			first = true;
			last = false;
		}
		else if(lastbutton.leftClicked())
		{
			//後攻
			AudioPlay(U"Button");

			//ボタン状態設定
			first = false;
			last = true;
		}
		else if (easyButton.leftClicked())
		{
			AudioPlay(U"Button");

			//ボタン状態設定
			easy = true;
			normal = false;
			hard = false;
		}
		else if (normalButton.leftClicked())
		{
			AudioPlay(U"Button");

			//ボタン状態設定
			easy = false;
			normal = true;
			hard = false;
		}
		else if (hardButton.leftClicked())
		{
			AudioPlay(U"Button");

			//ボタン状態設定
			easy = false;
			normal = false;
			hard = true;
		}
		else if (okButton.leftClicked())
		{
			AudioPlay(U"Button");

			//アニメーション用ストップウォッチ
			getData().stopwatch.restart();

			//カードシャッフル
			getData().cards.shuffle();

			//カード情報リセット
			CardsReset(getData().cards);
			getData().UsedCards.clear();

			//Player,CPU情報リセット
			getData().player.AllClear();
			getData().cpu.AllClear();

			//CPUの強さ,名前設定
			if (easy)
			{
				getData().cpu.setStrength(1);
				getData().cpu.setName(U"CPU(弱い)");
			}
			else if (normal)
			{
				getData().cpu.setStrength(2);
				getData().cpu.setName(U"CPU(普通)");
			}
			else if (hard)
			{
				getData().cpu.setStrength(3);
				getData().cpu.setName(U"CPU(強い)");
			}

			if (first)
			{
				//Memoryシーンにおける先攻,Betシーンにおけるファーストベットの設定
				getData().Memory_PlayerTurn = true;
				getData().Bet_PlayerFirst = true;
			}
			else if (last)
			{
				//Memoryシーンにおける先攻,Betシーンにおけるファーストベットの設定
				getData().Memory_PlayerTurn = false;
				getData().Bet_PlayerFirst = false;
			}
			//Betシーンのフラグリセット
			getData().RaiseMenu = false;

			//ラウンドリセット
			getData().Round = 1;

			//CPUの攻めっ気設定
			getData().cpu.setAggression(Random<double>(-0.1, 0.1));

			//神経衰弱画面(Memory)へ
			changeScene(State::Memory, getData().changeSec);
		}
		else if (cancelButton.leftClicked())
		{
			//キャンセル
			AudioPlay(U"Cancel");
			SelectFlg = false;
		}
	}
	else
	{
		//通常のタイトル画面
		if (startButton.mouseOver() || ruleButton.mouseOver() || configButton.mouseOver() || exitButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (startButton.leftClicked())
		{
			AudioPlay(U"Button");
			//先攻後攻選択画面へ
			SelectFlg = true;
		}
		else if (ruleButton.leftClicked())
		{
			AudioPlay(U"Button");
			//ルール説明へ
			getData().NowScene = U"Title";
			changeScene(State::Rule, getData().changeSec);
		}
		else if (configButton.leftClicked())
		{
			AudioPlay(U"Button");
			//設定画面へ
			getData().NowScene = U"Title";
			changeScene(State::Config, getData().changeSec);
		}
		else if (exitButton.leftClicked())
		{
			AudioPlay(U"Button");
			//終了
			System::Exit();
		}
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
	Button(startButton, FontAsset(U"Button"), U"スタート", Palette::Black, !SelectFlg);
	Button(ruleButton, FontAsset(U"Button"), U"遊び方", Palette::Black, !SelectFlg);
	Button(configButton, FontAsset(U"Button"), U"設定", Palette::Black, !SelectFlg);
	Button(exitButton, FontAsset(U"Button"), U"終了する", Palette::Black, !SelectFlg);

	if (SelectFlg)
	{
		//先攻後攻選択画面
		selectFrame.draw(Palette::White);
		selectFrame.drawFrame(2, 2, Palette::Black);

		FontAsset(U"Text")(U"先攻/後攻の選択").drawAt(800, 380, Palette::Black);
		Button(firstButton, FontAsset(U"Button"), U"先攻", Palette::Black, first);
		Button(lastbutton, FontAsset(U"Button"), U"後攻", Palette::Black, last);

		FontAsset(U"Text")(U"CPUの強さ").drawAt(800, 600, Palette::Black);
		Button(easyButton, FontAsset(U"Text"), U"弱い", Palette::Black, easy);
		Button(normalButton, FontAsset(U"Text"), U"普通", Palette::Black, normal);
		Button(hardButton, FontAsset(U"Text"), U"強い", Palette::Black, hard);
		Button(okButton, FontAsset(U"Button"), U"OK", Palette::Black);
		Button(cancelButton, FontAsset(U"Button"), U"キャンセル", Palette::Black);
	}
}
