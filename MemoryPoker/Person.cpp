#include "Person.hpp"

//コンストラクタ
Person::Person(String name) : FlipPair(-1, -1), Chip(500), Name(name) {}

//場からランダムにペアを選ぶ
void Person::SelectRandomPair(HashSet<int32> usedCards, Array<PlayingCard::Card> cards)
{
	int32 first = Random<int32>(0, 51), second = Random<int32>(0, 51);

	while (usedCards.contains(first))
	{
		first = Random<int32>(0, 51);
	}

	while (usedCards.contains(second) || first == second || cards[first].rank != cards[second].rank)
	{
		second = Random<int32>(0, 51);
	}

	if (first > second)
	{
		std::swap(first, second);
	}

	this->setFlipPair(first, second);
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

void Person::insertSelectCards(int32 insert_value)
{
	SelectCards << insert_value;
}

//指定した値(remove_value)の削除
void Person::removeFromSelectCards(int32 remove_value)
{
	//ラムダ式内で変数を用いるためキャプチャリスト(ラムダ式の[]内)に引数のremove_valueを追加しておく
	SelectCards.remove_if([remove_value](int32 n) { return n == remove_value; });
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

std::pair<int32, int32> Person::getFlipPair()
{
	return FlipPair;
}

void Person::setFlipPair(int32 first, int32 second)
{
	FlipPair.first = first;
	FlipPair.second = second;
}

Array<int32> Person::getHands()
{
	return Hands;
}

void Person::push_back_Hands(int32 card)
{
	Hands.push_back(card);
}
