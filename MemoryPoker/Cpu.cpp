#include "Cpu.hpp"

Cpu::Cpu(String name) : Person(name) {};

void Cpu::AllClear() {
	//基底クラス(Person)のAllClear呼び出し
	Person::AllClear();

	//記憶消去しておく
	Memory.clear();
}

//Memoryシーン内でのカード選択
int32 Cpu::SelectFirstCard(const Array<PlayingCard::Card> cards, const HashSet<int32> UsedCards)
{
	int32 resultSuit = -1;
	int32 resultRank = -1;
	int32 first = -1;

	//記憶を探索
	for (int32 i = 0; i < Memory.size(); i++)
	{
		for (int32 j = i + 1; j < Memory.size(); j++)
		{
			//記憶の中にペアがあればそれを選ぶ(できるだけ数字,スートが高いものを優先)
			if (cards[Memory[i]].rank == cards[Memory[j]].rank)
			{
				//比較用
				int32 tmpRank; //cardのランク
				int32 tmpIdx;  //インデックス
				int32 tmpSuit; //cardのスート

				//スートが高い方を選ぶ
				if (suitToint[cards[Memory[i]].suit] > suitToint[cards[Memory[j]].suit]) tmpIdx = Memory[i];
				else tmpIdx = Memory[j];

				tmpSuit = suitToint[cards[tmpIdx].suit];

				//1の場合は14に置き換えて考える
				if (cards[tmpIdx].rank == 1) tmpRank = 14;
				else tmpRank = cards[tmpIdx].rank;

				//rankが大きい,またはrankが同じでsuitが高いものを優先して選ぶ
				if ( (resultRank < tmpRank) || (resultRank == tmpRank && resultSuit < tmpSuit))
				{
					first = tmpIdx;
					resultRank = tmpRank;
					resultSuit = tmpSuit;
				}
			}
		}
	}

	//first != 1 (記憶からペアを選んだ)場合はそれを返す
	if (first != -1) return first;

	//記憶にない場合は完全ランダム選択とする
	first = Random<int32>(0, 51);

	while (UsedCards.contains(first))
	{
		first = Random<int32>(0, 51);
	}

	return first;
}

int32 Cpu::SelectSecondCard(const Array<PlayingCard::Card> cards, const HashSet<int32> UsedCards, const int32 first)
{
	int32 second = -1;
	int32 tmpSuit = -1;

	for (int i = 0; i < Memory.size(); i++)
	{
		//1枚目に選んでいるカードは無視
		if (Memory[i] == first) continue;

		//記憶の中にペアがあればそれを選ぶ
		if (cards[Memory[i]].rank == cards[first].rank)
		{
			if (tmpSuit < suitToint[cards[Memory[i]].suit])
			{
				second = Memory[i];
				tmpSuit = suitToint[cards[Memory[i]].suit];
			}
		}
	}

	//second != 1 (記憶からペアを選んだ)場合はそれを返す
	if (second != -1) return second;

	//記憶にない場合は完全ランダム選択とする
	second = Random<int32>(0, 51);

	while (UsedCards.contains(second) || second == first)
	{
		second = Random<int32>(0, 51);
	}

	return second;
}

//揃ったペアを記憶から削除
//Playerが揃えた場合も呼び出す
void Cpu::DeleteMemory(int32 first, int32 second)
{
	Memory.remove_if([first](int32 n) { return n == first; });
	Memory.remove_if([second](int32 n) { return n == second; });
}

//揃わなかったカードのペアを記憶
void Cpu::UpdateMemory(int32 first, int32 second)
{
	if(!Memory.contains(first)) Memory.push_back(first);
	if(!Memory.contains(second)) Memory.push_back(second);
}

//forgetRateに基づき記憶から削除
void Cpu::ForgetMemory()
{
	//RandomBool(p)は確率pでtrueを返す

	if (RandomBool(forgetRate[strength]) && !Memory.empty())
	{
		int32 number = Random<int32>(1, forgetNumber[strength]);

		//末尾削除をするのでシャッフルしておく(前の要素がずっと残ることを防ぐ)
		Memory.shuffle();

		//number枚忘れる(Memory.size()が0になった場合はそこで終わる)
		for (int i = 0; i < number && Memory.size() > 0; i++)
		{
			Memory.pop_back();
		}
	}
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
