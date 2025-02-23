#include <Siv3D.hpp> // Siv3D v0.6.14
#include "Common.hpp"
#include "Title.hpp"
#include "Config.hpp"
#include "Rule.hpp"

void Main()
{
	//実ウィンドウ,シーンサイズ設定
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(800, 600);
	Scene::Resize(1600, 1200);



	//アセット登録
	FontAsset::Register(U"Title", 70, Typeface::Regular);
	FontAsset::Register(U"Button", FontMethod::MSDF, 48, Typeface::Bold);
	FontAsset::Register(U"Text", 30);

	AudioAsset::Register(U"BGM", U"Sounds/Night_View.mp3", Loop::Yes);
	AudioAsset::Register(U"button", U"Sounds/button.mp3");
	AudioAsset::Register(U"cancel", U"Sounds/cancel.mp3");
	AudioAsset::Register(U"flip", U"Sounds/cardflip.mp3");
	AudioAsset::Register(U"coin", U"Sounds/coin.mp3");

	TextureAsset::Register(U"Start", U"Images/Start.png");
	TextureAsset::Register(U"MemoryGame", U"Images/MemoryGame.png");
	TextureAsset::Register(U"Select", U"Images/Select.png");
	TextureAsset::Register(U"Bet", U"Images/Bet.png");
	TextureAsset::Register(U"CallRaise", U"Images/CallRaise.png");
	TextureAsset::Register(U"ShowDown", U"Images/ShowDown.png");
	TextureAsset::Register(U"Config", U"Images/Config.png");

	//アセット事前ロード
	FontAsset::Load(U"Title");
	FontAsset::Load(U"Button");
	FontAsset::Load(U"Text");

	AudioAsset::Load(U"BGM");
	AudioAsset::Load(U"button");
	AudioAsset::Load(U"cancel");
	AudioAsset::Load(U"flip");
	AudioAsset::Load(U"coin");

	TextureAsset::Load(U"Start");
	TextureAsset::Load(U"MemoryGame");
	TextureAsset::Load(U"Select");
	TextureAsset::Load(U"Bet");
	TextureAsset::Load(U"CallRaise");
	TextureAsset::Load(U"ShowDown");
	TextureAsset::Load(U"Config");

	//シーン管理用
	App manager;
	manager.add<Title>(State::Title);
	manager.add<Config>(State::Config);
	manager.add<Rule>(State::Rule);
	

	AudioAsset(U"BGM").setVolume(0.2);
	AudioAsset(U"button").setVolume(0.2);
	AudioAsset(U"cancel").setVolume(0.2);
	AudioAsset(U"flip").setVolume(0.2);
	AudioAsset(U"coin").setVolume(0.2);

	//BGM再生
	AudioAsset(U"BGM").play();

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
