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
	SelectCard,
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
	const PlayingCard::Pack pack{ 75, Palette::Red }; //幅75ピクセル、背面が赤色のカードパック
	Array<PlayingCard::Card> cards = PlayingCard::CreateDeck(0, false); //デッキ作成、背面の状態で
};

using App = SceneManager<State, GameData>;
