#pragma once
#include <Siv3D.hpp>

//Playe,CPUはこのクラスを継承する

class Person
{
public:
	//コンストラクタ
	Person(String name);

	//場からランダムにペアを選ぶ
	void SelectRandomPair(HashSet<int32> usedCards, Array<PlayingCard::Card> cards);

	//初期状態に戻す(再スタート時など)
	void AllClear();

	Array<int32> getSelectCards();

	void insertRoleCards(PlayingCard::Card card);
	Array<PlayingCard::Card> getRoleCards();
	void RoleCardsClear();

	int32 getManNumber();
	void setMaxNumber(int32 number);
	int32 getMaxSuit();
	void setMaxSuit(int32 suit);
	String getName();
	int32 getChip();

protected:
	//intN -> Nbit符号付き整数
	Array<int32> Hands; //手札
	Array<int32> SelectCards; //勝負するときの選んだカード(3枚)
	int32 MaxSuit = 0; //役に含まれる一番強いスート
	int32 MaxNumber = 0; //役に含まれる一番強い数字
	int32 Role = 0; //役の強さ
	Array<PlayingCard::Card> RoleCards; //役に含まれるカード
	String Name; //名前
	std::pair<int32, int32> FlipPair; //めくったカードのcardsにおけるインデックスの組
	int32 Chip = 500; //チップ(最初は500)
	String RoleText; //役の名前
};
