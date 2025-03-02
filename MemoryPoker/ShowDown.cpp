#include "ShowDown.hpp"
#include "Button.hpp"

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
		changeScene(State::Config, getData().changeSec);
	}

	if (!CpuSelectCardFlip())
	{
		//CPUのカードめくり中
		
	}
	else if(CompRole(getData().player, getData().cpu))
	{
		//完了(Player勝利)

		//色変更
		PlayerRoleAreaColor = Palette::Yellow;
	}
	else
	{
		//完了(CPU勝利)

		//色変更
		CpuRoleAreaColor = Palette::Yellow;
	}

}

//描画関数
void ShowDown::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

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

	//PlayerRoleText表示
	PlayerRoleArea.draw(PlayerRoleAreaColor);
	PlayerRoleArea.drawFrame(2, 2, Palette::Black);
	//カードがすべてめくられた状態でのみ役を表示
	if (CpuSelectCardFlip()) FontAsset(U"Text")(getData().player.getRoleText()).drawAt(800, 750, Palette::Black);

	//CPU選択カード表示
	CpuSelectCardArea.draw(Palette::White);
	CpuSelectCardArea.drawFrame(2, 2, Palette::Black);
	for (int i = 0; i < getData().cpu.getSelectCards().size(); i++)
	{
		const Vec2 center{ 710 + i * 90, 250 };

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

	//CpuRoletext表示
	CpuRoleArea.draw(CpuRoleAreaColor);
	CpuRoleArea.drawFrame(2, 2, Palette::Black);
	//カードがすべてめくられた状態でのみ役を表示
	if (CpuSelectCardFlip()) FontAsset(U"Text")(getData().cpu.getRoleText()).drawAt(800, 450, Palette::Black);
}

//CpuのSelectCardを順に表にする
//全部表になっていればtrue,それ以外はfalseを返す
//draw関数内でも使用するためconstに(メンバ変数の読み書きはしていない)
bool ShowDown::CpuSelectCardFlip() const
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
