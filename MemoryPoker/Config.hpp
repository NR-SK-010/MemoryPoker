#pragma once
#include "Common.hpp"

class Config : public App::Scene
{
public:
	Config(const InitData& init);

	void update() override;

	void draw() const override;

private:
	RoundRect Frame{ 500, 250, 600, 600, 7 }; //外枠
	Rect CancelButton{ Arg::center(1060, 290), 50, 50 }; //キャンセルボタン
	Rect SoundTestButton{ Arg::center(650, 625), 200, 100 }; //サウンドテストボタン
	Rect RuleButton{ Arg::center(950, 625), 200, 100 }; //遊び方ボタン
	Rect ToExitButton{ Arg::center(800, 750), 400, 100 }; //タイトルに戻る

	//「タイトルに戻りますか」画面のボタン
	Rect ExitButton{ Arg::center(650, 700), 250, 100 };
	Rect ExitCancel{ Arg::center(950, 700), 250, 100 };

	//BGM調整用のボタン
	Array<Rect> BGMButtons = {
							   Rect{ Arg::center(760, 415), 25, 30 },
							   Rect{ Arg::center(800, 415), 25, 40 },
							   Rect{ Arg::center(840, 415), 25, 50 },
							   Rect{ Arg::center(880, 415), 25, 60 },
							   Rect{ Arg::center(920, 415), 25, 70 },
	};

	//効果音調整用のボタン
	Array<Rect> SoundButtons = {
								Rect{ Arg::center(760, 515), 25, 30 },
								Rect{ Arg::center(800, 515), 25, 40 },
								Rect{ Arg::center(840, 515), 25, 50 },
								Rect{ Arg::center(880, 515), 25, 60 },
								Rect{ Arg::center(920, 515), 25, 70 },
	};

	bool ExitMenu = false; //「タイトルに戻りますか」画面
};
