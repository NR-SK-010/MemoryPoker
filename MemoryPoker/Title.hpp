#pragma once
#include "Common.hpp"

//タイトル画面

class Title : public App::Scene
{
public:
	Title(const InitData& init);

	void update() override;

	void draw() const override;

private:
	//ボタン用長方形
	Rect startButton{ 650, 550, 300, 80 };
	Rect ruleButton{ 650, 650, 300, 80 };
	Rect configButton{ 650, 750, 300, 80 };
	Rect exitButton{ 650, 850, 300, 80 };

	//先攻、後攻選択画面を表示するかどうか
	bool SelectFlg = false;

	//先攻後攻選択画面用
	Rect selectFrame{ Arg::center(800, 600), 500, 500 }; //枠
	Rect firstButton{ Arg::center(670, 600), 200, 100 }; //先攻ボタン
	Rect lastbutton{ Arg::center(930, 600), 200, 100 }; //後攻ボタン
	Rect cancelButton{ Arg::center(800, 770), 250, 100 }; //キャンセルボタン
};
