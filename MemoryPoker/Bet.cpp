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

	if (getData().player.getTotalBet() == 0 && getData().cpu.getTotalBet() == 0)
	{
		//最初のベット

		if (getData().Bet_PlayerFirst)
		{
			//Player

		}
		else
		{
			//CPU

		}
	}
	else if (getData().RaiseMenu)
	{
		//レイズ額決定時

	}
	else
	{
		//通常

		if (CallButton.mouseOver() || ToRaiseButton.mouseOver() || FoldButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (CallButton.leftClicked())
		{
			AudioPlay(U"Button");
		}
		else if (ToRaiseButton.leftClicked())
		{
			AudioPlay(U"Button");
			getData().RaiseMenu = true;
		}
		else if(FoldButton.leftClicked())
		{
			AudioPlay(U"Button");
		}
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
	FontAsset(U"Text")(getData().player.getBet()).drawAt(1450, 970, Palette::Black);

	//ボタン表示
	Button(CallButton, FontAsset(U"Button"), U"コール", ButtonColor, !getData().RaiseMenu);
	Button(ToRaiseButton, FontAsset(U"Button"), U"レイズ", ButtonColor, !getData().RaiseMenu);
	Button(FoldButton, FontAsset(U"Button"), U"フォールド", ButtonColor, !getData().RaiseMenu);

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
	FontAsset(U"Text")(getData().cpu.getBet()).drawAt(350, 195, Palette::Black);

	if (getData().player.getTotalBet() == 0 && getData().cpu.getTotalBet() == 0 && getData().Bet_PlayerFirst)
	{
		//Player側の最初のベット時の表示
		BetRaiseArea.draw(Palette::White);
		BetRaiseArea.drawFrame(2, 2, Palette::Black);
		Button(BetButton, FontAsset(U"Button"), U"ベット", Palette::Black);
		
		FontAsset(U"Text")(getData().player.getBet()).drawAt(800, 550, Palette::Black);
		TriangleButton(leftButton, getData().player.getBet() - 10 >= 0);
		TriangleButton(rightButton, getData().player.getBet() + 10 <= 100);
		TriangleButton(upButton, getData().player.getBet() + 1 <= 100);
		TriangleButton(downButton, getData().player.getBet() - 1 >= 0);
	}
	else if (getData().RaiseMenu)
	{
		//レイズ額決定時
		BetRaiseArea.draw(Palette::White);
		BetRaiseArea.drawFrame(2, 2, Palette::Black);
		Button(RaiseButton, FontAsset(U"Button"), U"レイズ", Palette::Black);
		Button(RaiseCancelButton, FontAsset(U"Button"), U"キャンセル", Palette::Black);
		FontAsset(U"Text")(getData().player.getBet()).drawAt(800, 550, Palette::Black);

		//レイズは相手の合計ベット額よりも多くベットする必要がある
		TriangleButton(leftButton, getData().player.getTotalBet() + getData().player.getBet() - 10 > getData().cpu.getTotalBet());
		TriangleButton(rightButton, getData().player.getTotalBet() + getData().player.getBet() + 10 <= getData().player.getTotalBet() + 100);
		TriangleButton(upButton, getData().player.getTotalBet() + getData().player.getBet() + 1 <= getData().player.getTotalBet() + 100);
		TriangleButton(downButton, getData().player.getTotalBet() + getData().player.getBet() - 1 > getData().cpu.getTotalBet());
	}
}
