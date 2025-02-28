#pragma once
#include "Common.hpp"

//ベットシーン

class Bet : public App::Scene
{
public:
	Bet(const InitData& init);

	void update() override;

	void draw() const override;

private:
	Rect MenuButton{ Arg::center(1480, 70), 200, 80 }; //メニューボタン

};
