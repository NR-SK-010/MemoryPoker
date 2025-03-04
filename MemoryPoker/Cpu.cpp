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
	if (!Memory.contains(first)) Memory.push_back(first);
	if (!Memory.contains(second)) Memory.push_back(second);
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
	//ポットオッズ計算
	//(コールに必要な枚数) / (コールした後のポットの全体額)で求まる
	double diff = static_cast<double>(player_Totalbet - TotalBet); //相手のBet額
	double PotSize = static_cast<double>(player_Totalbet + TotalBet + diff);
	double PotOdds = diff / PotSize;

	//役の強さ(0～1.0)
	double RoleStrength = static_cast<double>(Role) / 6.0;

	//フォールドの閾値
	//強気(aggression高)ならフォールドしにくい
	double FoldBoundary = PotOdds - Max(aggression, 0.0);

	//ブラフかどうかの判定材料
	double BluffProb;

	if (TotalBet == 0)
	{
		//相手がファーストベットの場合
		BluffProb = Min(5.0, static_cast<double>(player_Totalbet) / 3.0);
	}
	else
	{
		//通常
		//増加前のサイズで計算(ブラフの場合は増額前のサイズによって影響が変わる)
		BluffProb = Min(1.0, diff / (static_cast<double>(TotalBet) * 2.0));
	}

	//ブラフ等も考慮した最終的な役の強さの算出
	//強気かどうかも考慮する
	double FinalRoleStrength = RoleStrength + BluffProb * aggression * 10;

	if (FinalRoleStrength >= 0.7 && RandomBool(RaiseRate[strength] + aggression))
	{
		//レイズ
		//現在の相手のベット額の1.2～2.0倍(厳密には1.9999...)範囲で調整
		TotalBet = (int32)(player_Totalbet * Random<double>(1.2, 2.0));
		ActionText = U"レイズ";
	}
	else if (FinalRoleStrength >= FoldBoundary)
	{
		//コール(またはオールイン)
		TotalBet = Min(InitChip, player_Totalbet);
		if (TotalBet == InitChip)ActionText = U"オールイン";
		else ActionText = U"コール";
	}
	else
	{
		//フォールド
		Fold = true;
		ActionText = U"フォールド";
	}
}

//最初のベット
void Cpu::FirstBet()
{
	//計算用にRoleをdoubleに(0～1.0)
	double RoleStrength = static_cast<double>(Role) / 6.0;
	//ブラフ時に加算するチップ
	double BluffChip = 0;

	//役の強さ、攻めっ気、ブラフに基づく計算
	if (Role < 3 && RandomBool(bluffRate[strength]))
	{
		//ブラフ
		BluffChip = Random<double>(0, bluffRate[strength] * (static_cast<double>(strength) / 3.0));
	}
	TotalBet = Min(Chip, (int32)(50 * (RoleStrength + aggression + BluffChip)));
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

void Cpu::setAggression(double value)
{
	aggression = value;
}
