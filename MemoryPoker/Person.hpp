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

	//自分の手札から最も強い役を作成
	void RecommendRole(Array<PlayingCard::Card> cards);

	//役の名前をセット
	void setRoleText(Array<PlayingCard::Card> cards);

	String getRoleText();

	Array<int32> getSelectCards();
	void insertSelectCards(int32 insert_value);
	void removeFromSelectCards(int32 remove_value);

	void insertRoleCards(PlayingCard::Card card);
	Array<PlayingCard::Card> getRoleCards();
	void RoleCardsClear();

	int32 getManNumber();
	void setMaxNumber(int32 number);
	int32 getMaxSuit();
	void setMaxSuit(int32 suit);
	String getName();
	int32 getChip();
	void setChip(int32 value);
	int32 getInitChip();
	void setInitChip(int32 value);
	String getActionText();
	void setActionText(String text);

	int32 getTotalBet();
	void setTotalBet(int32 value);

	int32 getBet();
	void setBet(int32 value);

	std::pair<int32, int32> getFlipPair();
	void setFlipPair(int32 first, int32 second);

	Array<int32> getHands();
	void push_back_Hands(int32 card);

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
	int32 TotalBet = 0; //合計のベット額
	int32 Bet = 0; //一回のベット額
	int32 InitChip = 500; //Betシーン時、最初に持っているチップ
	String ActionText = U""; //「ベット」のように行動を表示
};
