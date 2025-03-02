#pragma once
#include "Common.hpp"

//神経衰弱画面

class Memory : public App::Scene
{
public:
	Memory(const InitData& init);

	void update() override;

	void draw() const override;

private:
	//イージングの際に使用
	Vec2 CardMove(const Vec2 from, const Vec2 to, const double e) const;

	//Player側情報表示
	RoundRect PlayerCardsFrame{ Arg::center(800, 1050), 600, 200, 7 };
	RoundRect PlayerNameFrame{ Arg::center(1250, 995), 200, 70 , 7 };
	RoundRect PlayerChipFrame{ Arg::center(1350, 1100), 400, 100, 7 };

	//CPU側情報表示
	RoundRect CpuCardsFrame{ Arg::center(800, 150), 600, 200, 7 };
	RoundRect CpuNameFrame{ Arg::center(150, 90), 200, 70, 7 };
	RoundRect CpuChipFrame{ Arg::center(250, 195), 400, 100, 7 };

	//メニュー(設定)ボタン
	Rect MenuButton{ Arg::center(1480, 70), 200, 80 };
};
