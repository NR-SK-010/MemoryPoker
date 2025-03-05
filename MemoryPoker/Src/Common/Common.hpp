#pragma once
#include <Siv3D.hpp>
#include "../Player/Player.hpp"
#include "../Cpu/Cpu.hpp"

//関数
void AudioPlay(String name, double volume);
void CardsReset(Array<PlayingCard::Card>& cards);

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
	double BGMVolume = 1.0;  //BGM音量
	double SoundVolume = 1.0; //効果音音量
	String NowScene = U""; //現在のシーン名を格納(Rule,Configから戻る際に使用)
	Stopwatch stopwatch; //ストップウォッチ
	bool ConfigFlg = false; //設定画面からルール説明に行くときのみtrue
	s3d::SecondsF changeSec = 0.5s; //画面切り替えにかかる時間
	const PlayingCard::Pack pack{ 75, Palette::Red }; //幅75ピクセル、背面が赤色のカードパック
	Array<PlayingCard::Card> cards = PlayingCard::CreateDeck(0, false); //デッキ作成、背面の状態で
	Player player = Player(U"Player"); //プレイヤー
	Cpu cpu = Cpu(U"CPU"); //CPU
	HashSet<int32> UsedCards = {}; //ゲーム内で使用したカード(揃えられたカード)のインデックス保管
	bool Memory_PlayerTurn; //Memoryシーン内でプレイヤーの手番かどうか
	bool Bet_PlayerTurn; //Betシーン内でプレイヤーの手番かどうか
	bool Bet_PlayerFirst; //Betシーン内において、プレイヤーがファーストベットを行うか否か(神経衰弱の先攻/後攻と一致する)
	bool RaiseMenu = false; //Betシーンにおいてレイズ額決定メニューが表示されているか
	bool PlayerWin; //Betシーン内において,Playerが勝ったかどうか
	int32 Round = 1; //ラウンド数(全4ラウンド)
};

using App = SceneManager<State, GameData>;
