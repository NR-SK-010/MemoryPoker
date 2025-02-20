#include <Siv3D.hpp>

//効果音再生用関数
//音量変更に対応するため、play()で再生
//play()では音を重ねられないため要求時は効果音を一度止め、再び再生させる
void AudioPlay(String name)
{
	if (AudioAsset(name).isPlaying())
	{
		AudioAsset(name).stop();
		AudioAsset(name).play();
	}
	else
	{
		AudioAsset(name).play();
	}
}
