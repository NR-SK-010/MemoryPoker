#pragma once
#include <Siv3D.hpp>

//関数
void AudioPlay(String name);

//シーン名
enum class State
{
	Title,
	Config,
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
};

using App = SceneManager<State, GameData>;
