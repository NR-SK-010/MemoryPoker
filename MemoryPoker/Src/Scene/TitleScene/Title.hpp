﻿#pragma once
#include "../../Common/Common.hpp"

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

	//先攻/後攻 難易度選択画面を表示するかどうか
	bool SelectFlg = false;

	//先攻後攻/難易度選択画面用
	Rect selectFrame{ Arg::center(800, 600), 650, 600 }; //枠
	Rect firstButton{ Arg::center(720, 480), 150, 80 }; //先攻ボタン
	bool first = true; //先攻状態
	Rect lastbutton{ Arg::center(880, 480), 150, 80 }; //後攻ボタン
	bool last = false; //後攻状態
	Rect easyButton{ Arg::center(640, 700), 150, 80 }; //「弱い」ボタン
	bool easy = false; //「弱い」状態
	Rect normalButton{ Arg::center(800, 700), 150, 80 }; // 「普通」ボタン
	bool normal = true; //「普通」状態
	Rect hardButton{ Arg::center(960, 700), 150, 80 }; //「強い」ボタン
	bool hard = false; //「強い」状態
	Rect okButton{ Arg::center(650, 850), 250, 80 }; //OKボタン
	Rect cancelButton{ Arg::center(950, 850), 250, 80 }; //キャンセルボタン
};
