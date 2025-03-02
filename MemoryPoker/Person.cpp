#include "Person.hpp"
#include "HandEvaluator.hpp"

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
	TotalBet = 0;
	Bet = 0;
	InitChip = 500;
}

//次ラウンドのための準備
void Person::ForNextRound()
{
	Hands.clear();
	SelectCards.clear();
	MaxSuit = 0;
	MaxNumber = 0;
	Role = 0;
	RoleCards.clear();
	FlipPair.first = FlipPair.second = -1;
	RoleText = U"";
	TotalBet = 0;
	Bet = 0;
	InitChip = Chip;
}

//自分の手札から最も強い役を作成
void Person::RecommendRole(Array<PlayingCard::Card> cards)
{
	Person tmp = Person(U"");

	for (int32 idx : this->Hands)
	{
		tmp.Hands << idx;
	}
	tmp.SelectCards << tmp.Hands[0];
	tmp.SelectCards << tmp.Hands[1];
	tmp.SelectCards << tmp.Hands[2];
	tmp.Role = judge(cards, tmp);

	this->SelectCards.clear();
	this->Role = tmp.Role;
	this->SelectCards << tmp.SelectCards[0];
	this->SelectCards << tmp.SelectCards[1];
	this->SelectCards << tmp.SelectCards[2];
	this->MaxNumber = tmp.MaxNumber;
	this->MaxSuit = tmp.MaxSuit;

	for (int i = 0; i < tmp.Hands.size(); i++)
	{
		for (int j = i + 1; j < tmp.Hands.size(); j++)
		{
			for (int k = j + 1; k < tmp.Hands.size(); k++)
			{
				tmp.SelectCards.clear();
				tmp.SelectCards << tmp.Hands[i];
				tmp.SelectCards << tmp.Hands[j];
				tmp.SelectCards << tmp.Hands[k];
				tmp.Role = judge(cards, tmp);
				if (tmp.Role > this->Role)
				{
					//更新
					this->SelectCards.clear();
					this->Role = tmp.Role;
					this->SelectCards << tmp.SelectCards[0];
					this->SelectCards << tmp.SelectCards[1];
					this->SelectCards << tmp.SelectCards[2];
					this->MaxNumber = tmp.MaxNumber;
					this->MaxSuit = tmp.MaxSuit;
				}
				else if (tmp.Role == this->Role)
				{
					//役が同じ場合は最大の数字、それも同じ場合はスートで判断
					if (tmp.MaxNumber > this->MaxNumber || (tmp.MaxNumber == this->MaxNumber && tmp.MaxSuit > this->MaxSuit))
					{
						//更新
						this->SelectCards.clear();
						this->Role = tmp.Role;
						this->SelectCards << tmp.SelectCards[0];
						this->SelectCards << tmp.SelectCards[1];
						this->SelectCards << tmp.SelectCards[2];
						this->MaxNumber = tmp.MaxNumber;
						this->MaxSuit = tmp.MaxSuit;
					}
				}
			}
		}
	}
}

//役の名前をセット(SelectCard内に3枚ない場合は何もしない)
void Person::setRoleText(Array<PlayingCard::Card> cards)
{
	if (this->SelectCards.size() < 3)
	{
		this->RoleText = U"";
		return;
	}
		

	Person tmp = Person(U"tmp");
	tmp.SelectCards << this->SelectCards[0];
	tmp.SelectCards << this->SelectCards[1];
	tmp.SelectCards << this->SelectCards[2];
	this->Role = judge(cards, tmp);
	this->MaxNumber = tmp.MaxNumber;
	this->MaxSuit = tmp.MaxSuit;

	switch (this->Role)
	{
	case 0:
		this->RoleText = U"ハイカード";
		break;
	case 1:
		this->RoleText = U"ワンペア";
		break;
	case 2:
		this->RoleText = U"フラッシュ";
		break;
	case 3:
		this->RoleText = U"ストレート";
		break;
	case 4:
		this->RoleText = U"スリーカード";
		break;
	case 5:
		this->RoleText = U"ストレートフラッシュ";
		break;
	case 6:
		this->RoleText = U"ロイヤルストレートフラッシュ";
		break;
	default:
		break;
	}
}

String Person::getRoleText()
{
	return RoleText;
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

void Person::setName(String value)
{
	Name = value;
}

int32 Person::getChip()
{
	return Chip;
}

void Person::setChip(int32 value)
{
	Chip = value;
}

int32 Person::getInitChip()
{
	return InitChip;
}

void Person::setInitChip(int32 value)
{
	InitChip = value;
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

int32 Person::getTotalBet()
{
	return TotalBet;
}

void Person::setTotalBet(int32 value)
{
	TotalBet = value;
}

int32 Person::getBet()
{
	return Bet;
}

void Person::setBet(int32 value)
{
	Bet = value;
}

String Person::getActionText()
{
	return ActionText;
}

void Person::setActionText(String text)
{
	ActionText = text;
}

Array<int32> Person::getHands()
{
	return Hands;
}

void Person::push_back_Hands(int32 card)
{
	Hands.push_back(card);
}

int32 Person::getRole()
{
	return Role;
}

bool Person::getFold()
{
	return Fold;
}

void Person::setFold(bool value)
{
	Fold = value;
}
