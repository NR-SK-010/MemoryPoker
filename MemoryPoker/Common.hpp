#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"

//関数
void AudioPlay(String name);

//シーン名
enum class State
{
	Title,
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
	double BGMVolume = 1.0;  //BGM音量
	double SoundVolume = 1.0; //効果音音量
	String NowScene = U""; //現在のシーン名を格納(Ruleから戻る際に使用)
	Stopwatch stopwatch; //ストップウォッチ
};

using App = SceneManager<State, GameData>;
