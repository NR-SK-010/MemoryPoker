#pragma once
#include "../../Common/Common.hpp"

class Rule : public App::Scene
{
public:
	Rule(const InitData& init);

	void update() override;

	void draw() const override;

private:
	//写真埋め込み用
	Rect ImageArea{ 50, 100, 1500, 844 };
	Rect TextArea{ 50, 965, 1500, 220 };
	Rect ExitButton{ 1380, 20, 200, 60 };
	Triangle ToNextPageButton{ 1510, 1150, 50, 90_deg };
	Triangle ToPrePageButton{ 1450, 1150, 50, 270_deg };

	//画像
	Array<Texture> Images = { Texture{Resource(U"Images/Start.png")},
							  Texture{Resource(U"Images/MemoryGame.png")},
							  Texture{Resource(U"Images/Select.png")},
							  Texture{Resource(U"Images/Bet.png")},
							  Texture{Resource(U"Images/CallRaise.png")},
							  Texture{Resource(U"Images/ShouDown.png")},
							  Texture{Resource(U"Images/Config.png")}, };

	int page = 1;
};
