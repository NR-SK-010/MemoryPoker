#include "Person.hpp"

//コンストラクタ
Person::Person(String name) : FlipPair(-1, -1), Chip(500), Name(name) {}

//場からランダムにペアを選ぶ
void Person::SelectRandomPair(HashSet<int32> usedCards, Array<PlayingCard::Card> cards)
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
	RoleCards.clear();
	FlipPair.first = FlipPair.second = -1;
	Chip = 500;
	RoleText = U"";
}

Array<int32> Person::getSelectCards()
{
	return SelectCards;
}

void Person::insertRoleCards(PlayingCard::Card card)
{
	RoleCards << card;
}

Array<PlayingCard::Card> Person::getRoleCards()
{
	return RoleCards;
}

void Person::RoleCardsClear()
{
	RoleCards.clear();
}

int32 Person::getManNumber()
{
	return MaxNumber;
}

void Person::setMaxNumber(int32 number)
{
	MaxNumber = number;
}

int32 Person::getMaxSuit()
{
	return MaxSuit;
}

void Person::setMaxSuit(int32 suit)
{
	MaxSuit = suit;
}

String Person::getName()
{
	return Name;
}

int32 Person::getChip()
{
	return Chip;
}
