#pragma once
#include "Common.hpp"

//設定画面描画用クラス

class Config
{
public:
	//コンストラクタ
	Config(double& BGMVolume, double& SoundVolume);

	//更新関数
	//スライダーは関数の関係上更新関数側に
	void update();

	//描画関数
	void draw() const;

	//flg用プロパティ
	bool getFlg() const;
	void setFlg(const bool& configflg);

	//BGM,SoundVolumeゲッター
	double getBGMVolume();
	double getSoundVolume();

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

	bool flg = false; //設定画面が開かれているか
	bool ExitMenu = false; //「タイトルに戻りますか」画面
	double BGMVolume;
	double SoundVolume;
};
