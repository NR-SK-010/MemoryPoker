#pragma once
#include "../../Common/Common.hpp"

class ShowDown : public App::Scene
{
public:
	ShowDown(const InitData& init);

	void update() override;

	void draw() const override;

private:
	//CpuのSelectCardを順に表にする
	//全部表になっていればtrue,それ以外はfalseを返す
	bool CpuSelectCardFlip();

	//PlayerとCPUの役の比較
	//Player勝利でtrue,CPU勝利でfalseを返す
	bool CompRole(Player player, Cpu cpu);

	//チップの変動
	void ChipFluctuation(bool PlayerWin);

	//SelectCardsの描画
	void drawPlayerSelectCards() const;
	void drawCpuSelectCards() const;

	//RoleTextの描画
	void drawPlayerRoleText() const;
	void drawCpuRoleText() const;

	Rect MenuButton{ Arg::center(1480, 70), 200, 80 };//メニューボタン

	RoundRect PlayerSelectCardArea{ Arg::center(800, 950), 400, 200, 7 }; //Player選択カード表示エリア
	RoundRect PlayerNameArea{ Arg::center(1250, 865), 200, 70, 7 }; //PlayerName表示エリア
	RoundRect PlayerChipArea{ Arg::center(1350, 1100), 400, 100, 7 }; //PlayerChip表示エリア
	RoundRect PlayerBetArea{ Arg::center(1350, 970), 400, 100, 7 }; //PlayerBet額表示エリア
	RoundRect PlayerRoleArea{ Arg::center(800, 750), 700, 100, 7 }; //PlayerRoleText表示エリア
	Color PlayerRoleAreaColor = Palette::White; //PlayerRoleAreaの色(勝ったら黄色に変更)

	//Player描画用
	Array<int32> PlayerTmpSelectCards = {-1, -1, -1}; //描画用のカード
	String PlayerTmpRoleText = U"";


	RoundRect CpuSelectCardArea{ Arg::center(800, 250), 400, 200, 7 }; //CPU選択カード表示エリア
	RoundRect CpuNameArea{ Arg::center(150, 90), 200, 70, 7 }; //CPUName表示エリア
	RoundRect CpuChipArea{ Arg::center(250, 315), 400, 100, 7 }; //CpuChip表示エリア
	RoundRect CpuBetArea{ Arg::center(250, 195), 400, 100, 7 }; //CpuBet額表示エリア
	RoundRect CpuRoleArea{ Arg::center(800, 450), 700, 100, 7 }; //CpuRoleText表示エリア
	Color CpuRoleAreaColor = Palette::White; //CPURoleAreaの色(勝ったら黄色に変更)

	//CPU描画用
	Array<int32> CpuTmpSelectCards = { -1, -1, -1 }; //描画用のカード
	String CpuTmpRoleText = U"";
};
