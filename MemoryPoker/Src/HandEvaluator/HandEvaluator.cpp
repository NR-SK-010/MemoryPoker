#include "HandEvaluator.hpp"

int CountSameRankCards(Array<PlayingCard::Card> cards, Person& person)
{
	int count = 0;

	for (int i = 0; i < person.getSelectCards().size(); i++)
	{
		for (int j = i + 1; j < person.getSelectCards().size(); j++)
		{
			if (cards[person.getSelectCards()[i]].rank == cards[person.getSelectCards()[j]].rank)
			{
				if (!person.getRoleCards().contains(cards[person.getSelectCards()[i]]))
				{
					person.insertRoleCards(cards[person.getSelectCards()[i]]);
				}

				if (!person.getRoleCards().contains(cards[person.getSelectCards()[j]]))
				{
					person.insertRoleCards(cards[person.getSelectCards()[j]]);
				}
				count++;
			}
		}
	}

	return count;
}

bool IsOnePair(Array<PlayingCard::Card> cards, Person& person)
{
	if (CountSameRankCards(cards, person) == 1)
	{
		return true;
	}
	else
	{
		person.RoleCardsClear();
		return false;
	}
}

bool IsFlash(Array<PlayingCard::Card> cards, Person& person)
{
	for (int i = 0; i < person.getSelectCards().size() - 1; i++)
	{
		if (cards[person.getSelectCards()[i]].suit != cards[person.getSelectCards()[i + 1]].suit)
		{
			person.RoleCardsClear();
			return false;
		}
	}

	for (int i = 0; i < person.getSelectCards().size(); i++)
	{
		if (!person.getRoleCards().contains(cards[person.getSelectCards()[i]]))
		{
			person.insertRoleCards(cards[person.getSelectCards()[i]]);
		}
	}
	return true;
}

bool IsStraight(Array<PlayingCard::Card> cards, Person& person)
{
	Array<int32> tmpcards;
	for (int i = 0; i < person.getSelectCards().size(); i++)
	{
		tmpcards << cards[person.getSelectCards()[i]].rank;
	}
	tmpcards.sort();

	if (tmpcards[1] - tmpcards[0] == 1 && tmpcards[2] - tmpcards[1] == 1)
	{
		for (int i = 0; i < person.getSelectCards().size(); i++)
		{
			if (!person.getRoleCards().contains(cards[person.getSelectCards()[i]]))
			{
				person.insertRoleCards(cards[person.getSelectCards()[i]]);
			}
		}
		return true;
	}

	if (tmpcards[0] == 1 && tmpcards[1] == 12 && tmpcards[2] == 13)
	{
		for (int i = 0; i < person.getSelectCards().size(); i++)
		{
			if (!person.getRoleCards().contains(cards[person.getSelectCards()[i]]))
			{
				person.getRoleCards() << cards[person.getSelectCards()[i]];
			}
		}
		return true;
	}

	person.RoleCardsClear();
	return false;
}

bool IsThreeCard(Array<PlayingCard::Card> cards, Person& person)
{
	if (CountSameRankCards(cards, person) == 3)
	{
		for (int i = 0; i < person.getSelectCards().size(); i++)
		{
			if (!person.getRoleCards().contains(cards[person.getSelectCards()[i]]))
			{
				person.insertRoleCards(cards[person.getSelectCards()[i]]);
			}
		}
		return true;
	}
	else
	{
		person.RoleCardsClear();
		return false;
	}
}

bool IsStraightFlash(Array<PlayingCard::Card> cards, Person& person)
{
	if (IsStraight(cards, person) && IsFlash(cards, person))
	{
		for (int i = 0; i < person.getSelectCards().size(); i++)
		{
			if (!person.getRoleCards().contains(cards[person.getSelectCards()[i]]))
			{
				person.insertRoleCards(cards[person.getSelectCards()[i]]);
			}
		}
		return true;
	}
	else
	{
		person.RoleCardsClear();
		return false;
	}
}

bool IsRoyalStraightFlash(Array<PlayingCard::Card> cards, Person& person)
{
	if (IsStraightFlash(cards, person))
	{
		Array<int32> tmpcards;
		for (int i = 0; i < person.getSelectCards().size(); i++)
		{
			tmpcards << cards[person.getSelectCards()[i]].rank;
		}
		tmpcards.sort();
		if (tmpcards[0] == 1 && tmpcards[1] == 12 && tmpcards[2] == 13)
		{
			for (int i = 0; i < person.getSelectCards().size(); i++)
			{
				if (!person.getRoleCards().contains(cards[person.getSelectCards()[i]]))
				{
					person.insertRoleCards(cards[person.getSelectCards()[i]]);
				}
			}
			return true;
		}
		else
		{
			person.RoleCardsClear();
			return false;
		}

	}
	else
	{
		person.RoleCardsClear();
		return false;
	}
}


int judge(Array<PlayingCard::Card> cards, Person& person)
{
	int8 result = 0;
	person.RoleCardsClear();
	if (IsRoyalStraightFlash(cards, person))
	{
		result = 6;
	}
	else if (IsStraightFlash(cards, person))
	{
		result = 5;
	}
	else if (IsThreeCard(cards, person))
	{
		result = 4;
	}
	else if (IsStraight(cards, person))
	{
		result = 3;
	}
	else if (IsFlash(cards, person))
	{
		result = 2;
	}
	else if (IsOnePair(cards, person))
	{
		result = 1;
	}
	person.setMaxSuit(0); person.setMaxNumber(0);

	if (result == 3 || result == 5)
	{
		for (PlayingCard::Card firstCard : person.getRoleCards())
		{
			if (firstCard.rank == 1)
			{
				for (PlayingCard::Card secondCard : person.getRoleCards())
				{
					if (secondCard.rank == 12 || secondCard.rank == 13)
					{
						person.setMaxNumber(14);
					}
				}
			}
			if (person.getManNumber() < firstCard.rank)
			{
				person.setMaxNumber(firstCard.rank);
			}
		}
	}
	else
	{
		for (PlayingCard::Card card : person.getRoleCards())
		{
			if (card.rank == 1)
			{
				person.setMaxNumber(14);
			}
			if (person.getManNumber() < card.rank)
			{
				person.setMaxNumber(card.rank);
			}
		}
	}

	for (PlayingCard::Card card : person.getRoleCards())
	{
		if (person.getMaxSuit() < 4 && card.suit == PlayingCard::Suit::Spade)
		{
			person.setMaxSuit(4);
		}

		if (person.getMaxSuit() < 3 && card.suit == PlayingCard::Suit::Heart)
		{
			person.setMaxSuit(3);
		}

		if (person.getMaxSuit() < 2 && card.suit == PlayingCard::Suit::Diamond)
		{
			person.setMaxSuit(2);
		}

		if (person.getMaxSuit() < 1 && card.suit == PlayingCard::Suit::Club)
		{
			person.setMaxSuit(1);
		}
	}

	return result;
}
