#pragma once
#include "Common.hpp"

class Result : public App::Scene
{
public:
	Result(const InitData& init);

	void update() override;

	void draw() const override;

private:
	Rect MenuButton{ Arg::center(1480, 70), 200, 80 };//メニューボタン

	Rect TitleButton{ Arg::center(800, 1000), 300, 100 }; //タイトル遷移ボタン

	//Player情報
	RoundRect PlayerNameArea{ Arg::center(1250, 540), 180, 70, 7 };
	RoundRect PlayerChipArea{ Arg::center(1350, 645), 400, 100, 7 };

	//Cpu情報
	RoundRect CpuNameArea{ Arg::center(150, 540), 180, 70, 7 };
	RoundRect CpuChipArea{ Arg::center(250, 645), 400, 100, 7 };
};
