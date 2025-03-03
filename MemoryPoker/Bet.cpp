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

	//「コール」、「レイズ」、「フォールド」ボタン設定
	//通常時の条件分岐でのみtrueに
	CanPress = false;

	if (getData().player.getTotalBet() == 0 && getData().cpu.getTotalBet() == 0)
	{
		//最初のベット

		if (getData().Bet_PlayerFirst)
		{
			//Player
			if ((leftButton.mouseOver() && getData().player.getBet() - 1 >= 0) ||
				 (rightButton.mouseOver() && getData().player.getBet() + 1 <= Min(100, getData().player.getChip()) ) ||
				 (upButton.mouseOver() && getData().player.getBet() + 1 <= Min(100, getData().player.getChip())) ||
				 (downButton.mouseOver() && getData().player.getBet() - 1 >= 0) ||
				 (BetButton.mouseOver() && getData().player.getBet() > 0)
			)
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (leftButton.leftClicked() && getData().player.getBet() - 1 >= 0)
			{
				//-10
				AudioPlay(U"Button");
				getData().player.setBet(Max(0, getData().player.getBet() - 10));
			}
			else if (rightButton.leftClicked() && getData().player.getBet() + 1 <= Min(100, getData().player.getChip()))
			{
				//+10
				AudioPlay(U"Button");
				getData().player.setBet(Min( Min(100, getData().player.getChip()), getData().player.getBet() + 10));
			}
			else if (upButton.leftClicked() && getData().player.getBet() + 1 <= Min(100, getData().player.getChip()))
			{
				//+1
				AudioPlay(U"Button");
				getData().player.setBet(getData().player.getBet() + 1);
			}
			else if (downButton.leftClicked() && getData().player.getBet() - 1 >= 0)
			{
				//-1
				AudioPlay(U"Button");
				getData().player.setBet(getData().player.getBet() - 1);
			}
			else if (BetButton.leftClicked() && getData().player.getBet() > 0)
			{
				//ベット確定
				AudioPlay(U"Button");
				getData().player.setTotalBet(getData().player.getBet());
				getData().player.setActionText(U"ベット");

				//CPUに回す
				getData().Bet_PlayerTurn = false;
			}
		}
		else if (getData().stopwatch.sF() > 1.0) //1.0s待つ(シーン切り替えに0.5sかかるので実際は0.5s)
		{
			//CPU
			getData().cpu.FirstBet();

			//Playerに回す
			getData().Bet_PlayerTurn = true;
		}
	}
	else if (getData().RaiseMenu)
	{
		//レイズ額決定時
		if ((leftButton.mouseOver() && getData().player.getTotalBet() + getData().player.getBet() - 1 > getData().cpu.getTotalBet())  ||
			(rightButton.mouseOver() && getData().player.getBet() + 1 <= getData().player.getChip()) ||
			(upButton.mouseOver() && getData().player.getBet() + 1 <= getData().player.getChip())    ||
			(downButton.mouseOver() && getData().player.getTotalBet() + getData().player.getBet() - 1 > getData().cpu.getTotalBet())  ||
			(RaiseButton.mouseOver() && getData().player.getTotalBet() + getData().player.getBet() > getData().cpu.getTotalBet())     ||
			(RaiseCancelButton.mouseOver())
		)
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (leftButton.leftClicked() && getData().player.getTotalBet() + getData().player.getBet() - 1 > getData().cpu.getTotalBet())
		{
			//-10
			AudioPlay(U"Button");
			getData().player.setBet(Max(getData().cpu.getTotalBet() - getData().player.getTotalBet() + 1, getData().player.getBet() - 10));
		}
		else if (rightButton.leftClicked() && getData().player.getBet() + 1 <= getData().player.getChip())
		{
			//+10
			AudioPlay(U"Button");
			getData().player.setBet(Min(getData().player.getChip(), getData().player.getBet() + 10));
		}
		else if (upButton.leftClicked() && getData().player.getBet() + 1 <= getData().player.getChip())
		{
			//+1
			AudioPlay(U"Button");
			getData().player.setBet(getData().player.getBet() + 1);

		}
		else if (downButton.leftClicked() && getData().player.getTotalBet() + getData().player.getBet() - 1 > getData().cpu.getTotalBet())
		{
			//-1
			AudioPlay(U"Button");
			getData().player.setBet(getData().player.getBet() - 1);
		}
		else if (RaiseButton.leftClicked() && getData().player.getTotalBet() + getData().player.getBet() > getData().cpu.getTotalBet())
		{
			//レイズ決定
			AudioPlay(U"Button");
			getData().player.setTotalBet(getData().player.getTotalBet() + getData().player.getBet());
			getData().player.setActionText(U"レイズ");
			getData().RaiseMenu = false;

			//手番交代
			getData().Bet_PlayerTurn = false;
		}
		else if (RaiseCancelButton.leftClicked())
		{
			//レイズキャンセル
			AudioPlay(U"Cancel");
			getData().player.setBet(0);
			getData().RaiseMenu = false;
		}
	}
	else if ( (getData().player.getInitChip() != getData().player.getChip() + getData().player.getTotalBet()) ||
		      (getData().cpu.getInitChip() != getData().cpu.getChip() + getData().cpu.getTotalBet())
	)
	{
		//チップの増減
		AudioPlay(U"Coin");

		if (getData().player.getInitChip() < getData().player.getChip() + getData().player.getTotalBet())
		{
			getData().player.setChip(getData().player.getChip() - 1);
		}
		else if (getData().cpu.getInitChip() < getData().cpu.getChip() + getData().cpu.getTotalBet())
		{
			getData().cpu.setChip(getData().cpu.getChip() - 1);
		}

		if ((getData().player.getInitChip() == getData().player.getChip() + getData().player.getTotalBet()) ||
			(getData().cpu.getInitChip() < getData().cpu.getChip() + getData().cpu.getTotalBet()))
		{
			//チップ変動が終了
			//ストップウォッチをリスタートしておく(待機時間のため)
			getData().stopwatch.restart();
		}
	}
	else if (NextScene())
	{
		//TotalBetが同じorどちらかのチップが0枚(オールイン)orどちらかがフォールド
		// かつ ベット額表示等も完了(ひとつ上の分岐を抜けているので)しているとき
		//どちらもレイズしていないのでShowDownシーンへ遷移
		changeScene(State::ShowDown, getData().changeSec);
	}
	else if(getData().Bet_PlayerTurn && getData().player.getTotalBet() != getData().cpu.getTotalBet() && !getData().player.getFold())
	{
		//通常

		//「コール」、「レイズ」、「フォールド」ボタンはこの時だけ押せる
		CanPress = true;

		if (CallButton.mouseOver() || (ToRaiseButton.mouseOver() && CanRaise()) || FoldButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (CallButton.leftClicked())
		{
			//コールまたはオールイン
			AudioPlay(U"Button");

			//オールイン判定
			if (getData().player.getChip() + getData().player.getTotalBet() < getData().cpu.getTotalBet())
			{
				getData().player.setActionText(U"オールイン");
			}
			else
			{
				getData().player.setActionText(U"コール");
			}
			getData().player.setTotalBet(Min(getData().player.getInitChip(), getData().cpu.getTotalBet()));

			//手番交代
			getData().Bet_PlayerTurn = false;
		}
		else if (ToRaiseButton.leftClicked() && CanRaise())
		{
			//レイズ
			AudioPlay(U"Button");
			getData().RaiseMenu = true;

			//レイズ最低額の設定
			getData().player.setBet(getData().cpu.getTotalBet() - getData().player.getTotalBet() + 1);
		}
		else if(FoldButton.leftClicked())
		{
			//フォールド
			AudioPlay(U"Button");
			getData().player.setFold(true);

			getData().player.setActionText(U"フォールド");

			//ストップウォッチをリスタートしておく(待機時間のため)
			getData().stopwatch.restart();
		}
	}
	else if(getData().stopwatch.sF() > 0.5) //0.5s待つ
	{
		//CPUの行動
		getData().cpu.BetAction(getData().player.getTotalBet());
	}
}

//描画関数
void Bet::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	//メニューボタン
	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);

	//Player選択カード表示
	PlayerSelectCardArea.draw(Palette::White);
	PlayerSelectCardArea.drawFrame(2, 2, Palette::Black);
	for (int i = 0; i < getData().player.getSelectCards().size(); i++)
	{
		const Vec2 center{ 710 + i * 90, 950 };
		getData().pack(getData().cards[getData().player.getSelectCards()[i]]).drawAt(center);
	}

	//PlayerName表示
	PlayerNameArea.draw(Palette::White);
	PlayerNameArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().player.getName()).drawAt(1250, 865, Palette::Black);

	//PlayerChip表示
	PlayerChipArea.draw(Palette::White);
	PlayerChipArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"CHIP").drawAt(1250, 1100, Palette::Black);
	FontAsset(U"Text")(getData().player.getChip()).drawAt(1450, 1100, Palette::Black);

	//PlayerBet額表示
	PlayerBetArea.draw(Palette::White);
	PlayerBetArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"BET").drawAt(1250, 970, Palette::Black);
	FontAsset(U"Text")(getData().player.getInitChip() - getData().player.getChip()).drawAt(1450, 970, Palette::Black);

	//ボタン表示

	//オールイン判定
	if (getData().player.getChip() + getData().player.getTotalBet() < getData().cpu.getTotalBet())
	{
		Button(CallButton, FontAsset(U"Button"), U"オールイン", ButtonColor, CanPress);
	}
	else
	{
		Button(CallButton, FontAsset(U"Button"), U"コール", ButtonColor, CanPress);
	}
	Button(ToRaiseButton, FontAsset(U"Button"), U"レイズ", ButtonColor, CanPress && CanRaise());
	Button(FoldButton, FontAsset(U"Button"), U"フォールド", ButtonColor, CanPress);

	//CPU選択カード表示
	CpuSelectCardArea.draw(Palette::White);
	CpuSelectCardArea.drawFrame(2, 2, Palette::Black);
	for (int i = 0; i < getData().cpu.getSelectCards().size(); i++)
	{
		const Vec2 center{ 710 + i * 90, 250 };

		//表向きの場合は裏返しておく
		if (getData().cards[getData().cpu.getSelectCards()[i]].isFaceSide) getData().cards[getData().cpu.getSelectCards()[i]].flip();

		getData().pack(getData().cards[getData().cpu.getSelectCards()[i]]).drawAt(center);
	}

	//CpuName表示
	CpuNameArea.draw(Palette::White);
	CpuNameArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().cpu.getName()).drawAt(150, 90, Palette::Black);

	//CPUChip表示
	CpuChipArea.draw(Palette::White);
	CpuChipArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"CHIP").drawAt(150, 315, Palette::Black);
	FontAsset(U"Text")(getData().cpu.getChip()).drawAt(350, 315, Palette::Black);

	//CpuBet額表示
	CpuBetArea.draw(Palette::White);
	CpuBetArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"BET").drawAt(150, 195, Palette::Black);
	FontAsset(U"Text")(getData().cpu.getInitChip() - getData().cpu.getChip()).drawAt(350, 195, Palette::Black);

	if ( (getData().player.getInitChip() != getData().player.getChip() + getData().player.getTotalBet()) || getData().player.getFold() )
	{
		//チップ増減時(Playe側)
		PlayerActionArea.draw(Palette::White);
		PlayerActionArea.drawFrame(2, 2, Palette::Black);
		FontAsset(U"Text")(getData().player.getActionText()).drawAt(1350, 700, Palette::Black);
	}
	else if ( (getData().cpu.getInitChip() != getData().cpu.getChip() + getData().cpu.getTotalBet()) || getData().cpu.getFold() )
	{
		//チップ増減時(Playe側)
		CpuActionArea.draw(Palette::White);
		CpuActionArea.drawFrame(2, 2, Palette::Black);
		FontAsset(U"Text")(getData().cpu.getActionText()).drawAt(250, 500, Palette::Black);
	}

	if (getData().player.getTotalBet() == 0 && getData().cpu.getTotalBet() == 0 && getData().Bet_PlayerFirst)
	{
		//Player側の最初のベット時の表示
		BetRaiseArea.draw(Palette::White);
		BetRaiseArea.drawFrame(2, 2, Palette::Black);
		Button(BetButton, FontAsset(U"Button"), U"ベット", Palette::Black, getData().player.getBet() > 0);
		
		FontAsset(U"Text")(getData().player.getBet()).drawAt(800, 550, Palette::Black);
		TriangleButton(leftButton, getData().player.getBet() - 1 >= 0);
		TriangleButton(rightButton, getData().player.getBet() + 1 <= Min(100, getData().player.getChip()));
		TriangleButton(upButton, getData().player.getBet() + 1 <= Min(100, getData().player.getChip()));
		TriangleButton(downButton, getData().player.getBet() - 1 >= 0);
	}
	else if (getData().RaiseMenu)
	{
		//レイズ額決定時
		BetRaiseArea.draw(Palette::White);
		BetRaiseArea.drawFrame(2, 2, Palette::Black);
		Button(RaiseButton, FontAsset(U"Button"), U"レイズ", Palette::Black, getData().player.getTotalBet() + getData().player.getBet() > getData().cpu.getTotalBet());
		Button(RaiseCancelButton, FontAsset(U"Button"), U"キャンセル", Palette::Black);
		FontAsset(U"Text")(getData().player.getBet()).drawAt(800, 550, Palette::Black);

		//レイズは相手の合計ベット額よりも多くベットする必要がある
		TriangleButton(leftButton, getData().player.getTotalBet() + getData().player.getBet() - 1 > getData().cpu.getTotalBet());
		TriangleButton(rightButton, getData().player.getBet() + 1 <= getData().player.getChip());
		TriangleButton(upButton, getData().player.getBet() + 1 <= getData().player.getChip());
		TriangleButton(downButton, getData().player.getTotalBet() + getData().player.getBet() - 1 > getData().cpu.getTotalBet());
	}
}

//次のシーンに行くかどうかの判定
bool Bet::NextScene()
{
	//オールイン(チップ枚数が0枚かつ相手側のほうが総ベット額が高い状態)でのみtrue
	bool PlayerAllIn = getData().player.getChip() == 0 && (getData().cpu.getTotalBet() > getData().player.getTotalBet());
	bool CpuAllIn = getData().cpu.getChip() == 0 && (getData().cpu.getTotalBet() < getData().player.getTotalBet());

	//フォールドしているか
	bool FoldFlg = getData().player.getFold() || getData().cpu.getFold();

	//総ベット額が同じ(レイズしていない)
	bool CallFlg = getData().player.getTotalBet() == getData().cpu.getTotalBet();

	//上記4つのどれかがtrueかつ0.5s以上経過している状態でのみtrue
	return (FoldFlg || CallFlg || PlayerAllIn || CpuAllIn) && getData().stopwatch.sF() > 0.5;
}

//レイズ可能か
bool Bet::CanRaise() const
{
	return getData().player.getTotalBet() + getData().player.getChip() > getData().cpu.getTotalBet();
}
