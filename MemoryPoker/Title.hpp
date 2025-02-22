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

	//ボタンに表示するテキストのサイズ
	int32 buttonTextSize = 40;

	//設定画面用
	Config config = Config(getData().BGMVolume, getData().SoundVolume);
};
