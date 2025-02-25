#include "Person.hpp"

//コンストラクタ
Person::Person(String name) : FlipPair(-1, -1), Chip(500), Name(name) {}

//場からランダムにペアを選ぶ
void Person::SelectRandomPair(HashSet<int8> usedCards, Array<PlayingCard::Card> cards)
{

}

//初期状態に戻す(再スタート時など)
void Person::AllClear()
{
	Hands.clear();
	SelectCards.clear();
	MaxSuit = 0;
	MaxNumber = 0;
	Role = 0;
	FlipPair.first = FlipPair.second = -1;
	Chip = 500;
	RoleText = U"";
}
