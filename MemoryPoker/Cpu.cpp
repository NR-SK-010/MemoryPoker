#include "Cpu.hpp"

Cpu::Cpu(String name) : Person(name) {};

//Memoryシーン内でのカード選択
int32 Cpu::SelectFirstCard(const Array<PlayingCard::Card> cards, const HashSet<int32> UsedCards)
{
	//いったん完全ランダム選択とする(ゲームの処理が完成後行動パターンは作成)
	int32 selectcard = Random<int32>(0, 51);

	while (UsedCards.contains(selectcard))
	{
		selectcard = Random<int32>(0, 51);
	}

	return selectcard;
}

int32 Cpu::SelectSecondCard(const Array<PlayingCard::Card> cards, const HashSet<int32> UsedCards, const int32 firstcard)
{
	//いったん完全ランダム選択とする(ゲームの処理が完成後行動パターンは作成)
	int32 selectcard = Random<int32>(0, 51);

	while (UsedCards.contains(selectcard) || selectcard == firstcard)
	{
		selectcard = Random<int32>(0, 51);
	}

	return selectcard;
}

//揃ったペアを記憶から削除
void Cpu::DeleteMemory(int32 first, int32 second)
{
	//未実装
}

//記憶の更新(新しくカードを記憶、forgetRateに基づいた記憶の削除)
void Cpu::UpdateMemory()
{
	//未実装
}

//Betシーンでの行動選択
void Cpu::BetAction(int32 player_Totalbet)
{
	//コールのみ(具体的な行動は後で)
	TotalBet = Min(InitChip, player_Totalbet);
	ActionText = U"コール";
}

//最初のベット
void Cpu::FirstBet()
{
	//いったん固定
	TotalBet = 20;
	ActionText = U"ベット";
}

int32 Cpu::getStrength()
{
	return strength;
}

void Cpu::setStrength(int32 value)
{
	strength = value;
}
