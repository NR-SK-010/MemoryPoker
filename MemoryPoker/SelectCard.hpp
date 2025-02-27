#pragma once
#include "Common.hpp"

//手札から3枚選んで役を作る

class SelectCard : public App::Scene
{
public:
	SelectCard(const InitData& init);

	void update() override;

	void draw() const override;

private:
	Rect MenuButton{ Arg::center(1480, 70), 200, 80 }; //メニューボタン
	RoundRect PlayerHandsArea{ Arg::center(800, 1050), 600, 200, 7 }; //Player手札表示エリア
	RoundRect CpuHandsArea{ Arg::center(800, 200), 600, 250, 7 }; //CPU手札表示エリア
	RoundRect RoleNameArea{ 450, 550, 700, 100, 7 }; //役の名前表示エリア
	RoundRect SelectCardArea{ 500, 660, 600, 280 , 7 }; //選択したカードの表示エリア
	Rect RecommendButton{ 1200, 900, 300, 100 }; //「おすすめ」ボタン(カードの自動選択)
	Rect OkButton{ 1200, 1050, 300, 100 }; //「OK」ボタン。これを押すとBetシーンへ遷移
};
