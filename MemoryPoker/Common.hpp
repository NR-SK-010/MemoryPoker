#pragma once
#include <Siv3D.hpp>

//関数
void AudioPlay(String name);

//シーン名
enum class State
{
	Title,
	Config,
	Rule,
	Memory,
	Select,
	Bet,
	ShowDown,
	Result
};

//共有データ
struct GameData
{
	double BGMVolume = 0.2;  //BGM音量
	double SoundVolume = 0.2; //効果音音量
	String NowScene = U""; //現在のシーン名を格納(Rule,Configから戻る際に使用)
	Stopwatch stopwatch; //ストップウォッチ
	bool ConfigFlg = false; //設定画面からルール説明に行くときのみtrue
	s3d::SecondsF changeSec = 0.5s; //画面切り替えにかかる時間
};

using App = SceneManager<State, GameData>;
