#pragma once
#include <Siv3D.hpp>
#include "Person.hpp"

class Cpu : public Person
{
public:
	Cpu(String name);

	void AllClear() override;

	//Memoryシーン内でのカード選択
	int32 SelectFirstCard(const Array<PlayingCard::Card> cards, HashSet<int32> UsedCards);
	int32 SelectSecondCard(const Array<PlayingCard::Card> cards, HashSet<int32> UsedCards, const int32 first);

	//揃ったペアを記憶から削除
	void DeleteMemory(int32 first, int32 second);

	//揃わなかったカードのペアを記憶
	void UpdateMemory(int32 first, int32 second);

	//forgetRateに基づき記憶から削除
	void ForgetMemory();

	//Betシーンでの行動選択
	void FirstBet(); //最初のベット
	void BetAction(int32 player_Totalbet); //コール、レイズ、フォールドの選択

	int32 getStrength();
	void setStrength(int32 value);

	void setAggression(double value);
private:

	Array<int32> Memory; //めくったカードのインデックス格納(記憶)
	int32 strength = 2; //CPUの強さ(1:弱い、2:普通、3:強い)

	//忘れる確率(強さによって変わる)
	HashTable<int32, double> forgetRate = { {1, 0.7}, {2, 0.4}, {3, 0.1} };

	//忘れるカード枚数の最大値(強さによって変わる)
	HashTable<int32, int32> forgetNumber = { {1, 6}, {2, 4}, {3, 2} };

	//スートをintに変換する
	HashTable<PlayingCard::Suit, int32> suitToint = { {PlayingCard::Suit::Spade, 4},
													  {PlayingCard::Suit::Heart, 3},
													  {PlayingCard::Suit::Diamond, 2},
													  {PlayingCard::Suit::Club, 1}
													};

	//攻めっ気(強気か弱気か)の設定(毎回ランダムで-0.1～0.1の間の値を取る)
	double aggression = 0;
	


	//ブラフ設定(強さによって変わる)
	HashTable<int32, int32> bluffRate = { {1, 0.1}, {2, 0.3}, {3, 0.5} };

	//レイズする基本確率(強さと強気かどうかで変動)
	HashTable<int32, double> RaiseRate = { {1, 0.1}, {2, 0.15}, {3, 0.2} };
};
