#pragma once
#include <Siv3D.hpp>

//Playe,CPUはこのクラスを継承する

class Person
{
public:
	//コンストラクタ
	Person(String name);

	//場からランダムにペアを選ぶ
	void SelectRandomPair(HashSet<int8> usedCards, Array<PlayingCard::Card> cards);

	//初期状態に戻す(再スタート時など)
	void AllClear();

private:
	//intN -> Nbit符号付き整数
	Array<int8> Hands; //手札
	Array<int8> SelectCards; //勝負するときの選んだカード(3枚)
	int8 MaxSuit = 0; //役に含まれる一番強いスート
	int8 MaxNumber = 0; //役に含まれる一番強い数字
	int8 Role = 0; //役の強さ
	String Name; //名前
	std::pair<int8, int8> FlipPair; //めくったカードのcardsにおけるインデックスの組
	int16 Chip = 500; //チップ(最初は500)
	String RoleText; //役の名前
};
