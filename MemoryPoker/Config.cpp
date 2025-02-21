#include <Siv3D.hpp>
#include "Button.hpp"
#include "Config.hpp"

//コンストラクタ
Config::Config(String SceneName, double& BGMVolume, double& SoundVolume)
{
	PreScene = SceneName;
	this->BGMVolume = BGMVolume;
	this->SoundVolume = SoundVolume;
	flg = false;
}

//更新関数
void Config::update()
{
	if (CancelButton.mouseOver() || SoundTestButton.mouseOver() || RuleButton.mouseOver() || (PreScene != U"Title" && ToExitButton.mouseOver()))
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (CancelButton.leftClicked())
	{
		AudioPlay(U"cancel");
		flg = false;
	}
	else if (SoundTestButton.leftClicked())
	{
		AudioPlay(U"button");
	}
	else if (RuleButton.leftClicked())
	{
		AudioPlay(U"button");
	}
	else if (PreScene != U"Title" && ToExitButton.mouseOver())
	{
		AudioPlay(U"button");
	}
}

//描画関数
void Config::draw() const
{
	//外枠
	Frame.draw(Palette::White);
	Frame.drawFrame(3, 3, Palette::Black);

	Button(CancelButton, FontAsset(U"Button"), U"✕", Palette::Black);
	Button(SoundTestButton, FontAsset{ U"Button" }, U"テスト", Palette::Black);
	Button(RuleButton, FontAsset(U"Button"), U"遊び方", Palette::Black);
	if(PreScene != U"Title")Button(ToExitButton, FontAsset(U"Button"), U"タイトルに戻る", Palette::Black);

	FontAsset(U"Text")(U"音量調整").drawAt(800, 300, Palette::Black);
	FontAsset(U"Text")(U"BGM").drawAt(650, 415, Palette::Black);
	//スライダーが使えない(SimpleGUIが使えないので)->別の音量調整を考える
	FontAsset(U"Text")(U"効果音").drawAt(650, 515, Palette::Black);
}

//flg用プロパティ
bool Config::getFlg() const
{
	return flg;
}

void Config::setFlg(const bool& configflg)
{
	this->flg = configflg;
}
