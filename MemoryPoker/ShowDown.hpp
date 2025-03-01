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
};
