#pragma once
#include "Common.hpp"

class ShowDown : public App::Scene
{
public:
	ShowDown(const InitData& init);

	void update() override;

	void draw() const override;

private:
	Rect MenuButton{ Arg::center(1480, 70), 200, 80 };//メニューボタン

	RoundRect PlayerSelectCardArea{ Arg::center(800, 950), 400, 200, 7 }; //Player選択カード表示エリア
	RoundRect PlayerNameArea{ Arg::center(1250, 865), 180, 70, 7 }; //PlayerName表示エリア
	RoundRect PlayerChipArea{ Arg::center(1350, 1100), 400, 100, 7 }; //PlayerChip表示エリア
	RoundRect PlayerBetArea{ Arg::center(1350, 970), 400, 100, 7 }; //PlayerBet額表示エリア
	RoundRect PlayerRoleArea{ Arg::center(800, 750), 700, 100, 7 }; //PlayerRoleText表示エリア

	RoundRect CpuSelectCardArea{ Arg::center(800, 250), 400, 200, 7 }; //CPU選択カード表示エリア
	RoundRect CpuNameArea{ Arg::center(150, 90), 180, 70, 7 }; //CPUName表示エリア
	RoundRect CpuChipArea{ Arg::center(250, 315), 400, 100, 7 }; //CpuChip表示エリア
	RoundRect CpuBetArea{ Arg::center(250, 195), 400, 100, 7 }; //CpuBet額表示エリア
	RoundRect CpuRoleArea{ Arg::center(800, 450), 700, 100, 7 }; //CpuRoleText表示エリア
};
