#include "ShowDown.hpp"
#include "../../Button/Button.hpp"

//コンストラクタ
ShowDown::ShowDown(const InitData& init)
	: IScene{ init } {
}

//更新関数
void ShowDown::update()
{
	if (MenuButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (MenuButton.leftClicked())
	{
		AudioPlay(U"Button");
		getData().NowScene = U"ShowDown";

		//設定画面を開くときは一時停止
		getData().stopwatch.pause();

		changeScene(State::Config, getData().changeSec);
	}

	if (!CpuSelectCardFlip())
	{
		//CPUのカードめくり中

		//勝敗もセットしておく
		getData().PlayerWin = CompRole(getData().player, getData().cpu);

		//update -> drawの順で呼び出される
		// また、フェードイン、アウト時はdrawのみが呼び出される
		//そのため、次ラウンド準備でHands等をClear -> Clearされた状態で0画面が見えてしまう時間帯が生じる
		//対策として、描画用のものを代わりに用意しておく(draw関数内の該当箇所もそれに応じて書き直す)
		PlayerTmpSelectCards[0] = getData().player.getSelectCards()[0];
		PlayerTmpSelectCards[1] = getData().player.getSelectCards()[1];
		PlayerTmpSelectCards[2] = getData().player.getSelectCards()[2];
		PlayerTmpRoleText = getData().player.getRoleText();

		CpuTmpSelectCards[0] = getData().cpu.getSelectCards()[0];
		CpuTmpSelectCards[1] = getData().cpu.getSelectCards()[1];
		CpuTmpSelectCards[2] = getData().cpu.getSelectCards()[2];
		CpuTmpRoleText = getData().cpu.getRoleText();
	}
	else if (getData().player.getTotalBet() == 0 && getData().cpu.getTotalBet() == 0)
	{
		//チップ変動が終了
		// 2.0s経過したら次ラウンド,または結果画面へ
		if (getData().stopwatch.sF() > 2.0)
		{
			//Player,CPUの次ラウンド準備
			getData().player.ForNextRound();
			getData().cpu.ForNextRound();

			//ラウンド加算
			getData().Round++;

			//最初のベット入れ替え
			getData().Bet_PlayerFirst = !getData().Bet_PlayerFirst;

			//神経衰弱の最初の手番設定(Bet_PlayerTurnと一致)
			getData().Memory_PlayerTurn = getData().Bet_PlayerFirst;

			//効果音終了までは必ず待つ
			if ((getData().Round == 5 || getData().player.getChip() == 0 || getData().cpu.getChip() == 0) && !AudioAsset(U"Coin").isPlaying())
			{
				//4ラウンド終了,またはどちらかのチップが0枚になるとリザルト画面へ遷移
				changeScene(State::Result, getData().changeSec);
			}
			else if(!AudioAsset(U"Coin").isPlaying())
			{
				//次ラウンドへ
				changeScene(State::Memory, getData().changeSec);
			}
		}

	}
	else if(getData().PlayerWin)
	{
		//完了(Player勝利)

		//色変更
		PlayerRoleAreaColor = Palette::Yellow;
		ChipFluctuation(getData().PlayerWin);
	}
	else
	{
		//完了(CPU勝利)

		//色変更
		CpuRoleAreaColor = Palette::Yellow;
		ChipFluctuation(getData().PlayerWin);
	}

}

//描画関数
void ShowDown::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);

	//Player選択カード表示
	//フォールド時は灰色背景にしておく
	if(getData().player.getFold())PlayerSelectCardArea.draw(Palette::Gray);
	else PlayerSelectCardArea.draw(Palette::White);

	PlayerSelectCardArea.drawFrame(2, 2, Palette::Black);
	drawPlayerSelectCards();

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
	FontAsset(U"Text")(getData().player.getTotalBet()).drawAt(1450, 970, Palette::Black);

	//PlayerRoleText表示
	PlayerRoleArea.draw(PlayerRoleAreaColor);
	PlayerRoleArea.drawFrame(2, 2, Palette::Black);
	//カードがすべてめくられた状態でのみ役を表示
	drawPlayerRoleText();

	//CPU選択カード表示
	//フォールド時は灰色背景にしておく
	if(getData().cpu.getFold()) CpuSelectCardArea.draw(Palette::Gray);
	else CpuSelectCardArea.draw(Palette::White);

	CpuSelectCardArea.drawFrame(2, 2, Palette::Black);
	drawCpuSelectCards();

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
	FontAsset(U"Text")(getData().cpu.getTotalBet()).drawAt(350, 195, Palette::Black);

	//CpuRoletext表示
	CpuRoleArea.draw(CpuRoleAreaColor);
	CpuRoleArea.drawFrame(2, 2, Palette::Black);
	//カードがすべてめくられた状態でのみ役を表示
	drawCpuRoleText();
}




//CpuのSelectCardを順に表にする
//全部表になっていればtrue,それ以外はfalseを返す
//draw関数内でも使用するためconstに(メンバ変数の読み書きはしていない)
bool ShowDown::CpuSelectCardFlip()
{
	bool result = true;

	//0.5sは待機
	if (getData().stopwatch.sF() < 0.5) return false;

	for (int i = 0; i < getData().cpu.getSelectCards().size(); i++)
	{
		if (!getData().cards[getData().cpu.getSelectCards()[i]].isFaceSide)
		{
			if (i == 0 && getData().stopwatch.sF() < 1.0)
			{
				//0枚目(1枚目)のみシーン遷移に0.5sかかっているので1.0s待機
				//ShowDownシーンでの待機時間は実質0.5s
				result = false;
				break;
			}

			//表向きでない場合は裏返す
			AudioPlay(U"Flip");
			getData().cards[getData().cpu.getSelectCards()[i]].flip();

			//裏返したらストップウォッチはリスタート
			getData().stopwatch.restart();

			//1枚ずつ裏返す
			result = false;
			break;
		}
	}

	return result;
}

//PlayerとCPUの役の比較
//Player勝利でtrue,CPU勝利でfalseを返す
bool ShowDown::CompRole(Player player, Cpu cpu)
{
	//どちらかがフォールドしていた場合
	if (player.getFold()) return false;
	else if (cpu.getFold()) return true;

	bool result = false;

	if (player.getRole() > cpu.getRole())
	{
		result = true;
	}
	else if(player.getRole() == cpu.getRole())
	{
		if (player.getManNumber() > cpu.getManNumber())
		{
			result = true;
		}
		else if (player.getManNumber() == cpu.getManNumber() && player.getMaxSuit() > cpu.getMaxSuit())
		{
			result = true;
		}
	}

	return result;
}

//チップの変動
void ShowDown::ChipFluctuation(bool PlayerWin)
{
	if (CoinTimer == 0.0)
	{
		AudioPlay(U"Coin");
	}
	else if (CoinTimer > 1.0)
	{
		CoinTimer = 0.0;
	}
	//経過時間加算
	CoinTimer += Scene::DeltaTime();

	if (PlayerWin)
	{
		//Player勝利	
		
		if (getData().cpu.getTotalBet() > 0)
		{
			getData().cpu.setTotalBet(getData().cpu.getTotalBet() - 1);
		}
		else
		{
			getData().player.setTotalBet(getData().player.getTotalBet() - 1);
		}
		getData().player.setChip(getData().player.getChip() + 1);
	}
	else
	{
		//CPU勝利

		if (getData().player.getTotalBet() > 0)
		{
			getData().player.setTotalBet(getData().player.getTotalBet() - 1);
		}
		else
		{
			getData().cpu.setTotalBet(getData().cpu.getTotalBet() - 1);
		}
		getData().cpu.setChip(getData().cpu.getChip() + 1);
	}

	if (getData().player.getTotalBet() == 0 && getData().cpu.getTotalBet() == 0)
	{
		//次のシーンへの遷移までの待機時間のためにリスタート
		getData().stopwatch.restart();
	}
}

//PlayerのSelectCardsの描画
void ShowDown::drawPlayerSelectCards() const
{
	//SelectCardsの状態によって切り替える
	if (getData().player.getSelectCards().empty())
	{
		for (int i = 0; i < PlayerTmpSelectCards.size() ; i++)
		{
			const Vec2 center{ 710 + i * 90, 950 };
			getData().pack(getData().cards[PlayerTmpSelectCards[i]]).drawAt(center);
		}
	}
	else
	{
		for (int i = 0; i < getData().player.getSelectCards().size(); i++)
		{
			const Vec2 center{ 710 + i * 90, 950 };
			getData().pack(getData().cards[getData().player.getSelectCards()[i]]).drawAt(center);
		}
	}
	
}
//CpuのSelectCardsの描画
void ShowDown::drawCpuSelectCards() const
{
	//SelectCardsの状態によって切り替える
	if (getData().cpu.getSelectCards().empty())
	{
		for (int i = 0; i < CpuTmpSelectCards.size(); i++)
		{
			const Vec2 center{ 710 + i * 90, 250 };
			getData().pack(getData().cards[CpuTmpSelectCards[i]]).drawAt(center);
		}
	}
	else
	{
		for (int i = 0; i < getData().cpu.getSelectCards().size(); i++)
		{
			const Vec2 center{ 710 + i * 90, 250 };
			getData().pack(getData().cards[getData().cpu.getSelectCards()[i]]).drawAt(center);
		}
	}
}

//RoleTextの描画
void ShowDown::drawPlayerRoleText() const
{
	//SelectCardsの状態によって切り替える
	if (getData().player.getSelectCards().empty())
	{
		if(getData().cards[PlayerTmpSelectCards[2]].isFaceSide) FontAsset(U"Text")(PlayerTmpRoleText).drawAt(800, 750, Palette::Black);
	}
	else
	{
		if(getData().cards[getData().player.getSelectCards()[2]].isFaceSide) FontAsset(U"Text")(getData().player.getRoleText()).drawAt(800, 750, Palette::Black);
	}
}

void ShowDown::drawCpuRoleText() const
{
	//SelectCardsの状態によって切り替える
	if (getData().cpu.getSelectCards().empty())
	{
		if (getData().cards[CpuTmpSelectCards[2]].isFaceSide) FontAsset(U"Text")(CpuTmpRoleText).drawAt(800, 450, Palette::Black);
	}
	else
	{
		if (getData().cards[getData().cpu.getSelectCards()[2]].isFaceSide) FontAsset(U"Text")(getData().cpu.getRoleText()).drawAt(800, 450, Palette::Black);
	}
}
