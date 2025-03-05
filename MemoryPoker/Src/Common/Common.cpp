#include <Siv3D.hpp>
#include "Common.hpp"

//効果音再生用関数
//音量変更に対応するため、playOneShot()で再生
//要求時は効果音を一度止め、再び再生させる
void AudioPlay(String name, double volume)
{
	if (AudioAsset(name).isPlaying())
	{
		AudioAsset(name).stop();
		AudioAsset(name).playOneShot(volume);
	}
	else
	{
		AudioAsset(name).playOneShot(volume);
	}
}

void CardsReset(Array<PlayingCard::Card>& cards)
{
	for (int i : step(13 * 4))
	{
		if (cards[i].isFaceSide)
		{
			cards[i].flip();
		}
	}
}
