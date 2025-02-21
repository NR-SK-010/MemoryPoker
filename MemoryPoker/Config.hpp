#pragma once
#include "Common.hpp"

//設定画面描画用クラス

class Config
{
public:
	//コンストラクタ
	Config(String SceneName, double& BGMVolume, double& SoundVolume);

	//更新関数
	//スライダーは関数の関係上更新関数側に
	void update();

	//描画関数
	void draw() const;

	//flg用プロパティ
	bool getFlg() const;
	void setFlg(const bool& configflg);

private:
	RoundRect Frame{ 500, 250, 600, 600, 7 }; //外枠
	Rect CancelButton{ Arg::center(1060, 290), 50, 50 }; //キャンセルボタン
	Rect SoundTestButton{ Arg::center(650, 625), 200, 100 }; //サウンドテストボタン
	Rect RuleButton{ Arg::center(950, 625), 200, 100 };
	Rect ToExitButton{ Arg::center(800, 750), 400, 100 }; //タイトルに戻る

	Rect ExitButton{ Arg::center(650, 700), 250, 100 };
	Rect ExitCancel{ Arg::center(950, 700), 250, 100 };

	String PreScene; //設定画面を開いたときのシーン名

	bool flg = false; //設定画面が開かれているか
	double BGMVolume;
	double SoundVolume;
};
