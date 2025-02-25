#pragma once
#include <Siv3D.hpp>
#include "Person.hpp"


int CountSameRankCards(Array<PlayingCard::Card> cards, Person& person);
bool IsOnePair(Array<PlayingCard::Card> cards, Person& person);
bool IsFlash(Array<PlayingCard::Card> cards, Person& person);
bool IsStraight(Array<PlayingCard::Card> cards, Person& person);
bool IsThreeCard(Array<PlayingCard::Card> cards, Person& person);
bool IsStraightFlash(Array<PlayingCard::Card> cards, Person& person);
bool IsRoyalStraightFlash(Array<PlayingCard::Card> cards, Person& person);
int judge(Array<PlayingCard::Card> cards, Person& person);
