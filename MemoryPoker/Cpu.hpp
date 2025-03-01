#pragma once
#include <Siv3D.hpp>
#include "Person.hpp"

class Cpu : public Person
{
public:
	Cpu(String name);

	//Memoryシーン内でのカード選択
	int32 SelectFirstCard(const Array<PlayingCard::Card> cards, HashSet<int32> UsedCards);
	int32 SelectSecondCard(const Array<PlayingCard::Card> cards, HashSet<int32> UsedCards, const int32 firstcard);

	//揃ったペアを記憶から削除
	void DeleteMemory(int32 first, int32 second);

	//記憶の更新(新しくカードを記憶、forgetRateに基づいた記憶の削除)
	void UpdateMemory();

	//Betシーンでの行動選択
	void FirstBet(); //最初のベット
	void BetAction(int32 player_Totalbet); //コール、レイズ、フォールドの選択


private:
	Array<int32> Memory; //めくったカードのインデックス格納(記憶)
	double forgetRate = 0.5; //忘れる確率
};
