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

};

using App = SceneManager<State, GameData>;
