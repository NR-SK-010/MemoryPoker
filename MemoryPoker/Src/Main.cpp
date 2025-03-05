#include <Siv3D.hpp> // Siv3D v0.6.14
#include "Common/Common.hpp"
#include "Scene/TitleScene/Title.hpp"
#include "Scene/ConfigScene/Config.hpp"
#include "Scene/RuleScene/Rule.hpp"
#include "Scene/MemoryScene/Memory.hpp"
#include "Scene/SelectCardScene/SelectCard.hpp"
#include "Scene/BetScene/Bet.hpp"
#include "Scene/ShowDownScene/ShowDown.hpp"
#include "Scene/ResultScene/Result.hpp"

void Main()
{
	//実ウィンドウ,シーンサイズ設定
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(800, 600);
	Scene::Resize(1600, 1200);



	//アセット登録
	FontAsset::Register(U"Title", 70, Typeface::Regular);
	FontAsset::Register(U"Result", FontMethod::MSDF, 100, Typeface::Bold);
	FontAsset::Register(U"Button", FontMethod::MSDF, 40, Typeface::Bold);
	FontAsset::Register(U"Text", 35, Typeface::Bold);
	FontAsset::Register(U"RuleText", 30);

	AudioAsset::Register(U"BGM", U"../App/Sounds/Night_View.mp3", Loop::Yes);
	AudioAsset::Register(U"Button", U"../App/Sounds/button.mp3");
	AudioAsset::Register(U"Cancel", U"../App/Sounds/cancel.mp3");
	AudioAsset::Register(U"Flip", U"../App/Sounds/cardflip.mp3");
	AudioAsset::Register(U"Coin", U"../App/Sounds/coin.mp3");

	TextureAsset::Register(U"Start", U"../App/Images/Start.png");
	TextureAsset::Register(U"MemoryGame", U"../App/Images/MemoryGame.png");
	TextureAsset::Register(U"Select", U"../App/Images/Select.png");
	TextureAsset::Register(U"Bet", U"../App/Images/Bet.png");
	TextureAsset::Register(U"CallRaise", U"../App/Images/CallRaise.png");
	TextureAsset::Register(U"ShowDown", U"../App/Images/ShowDown.png");
	TextureAsset::Register(U"Config", U"../App/Images/Config.png");

	//アセット事前ロード
	FontAsset::Load(U"Title");
	FontAsset::Load(U"Result");
	FontAsset::Load(U"Button");
	FontAsset::Load(U"Text");
	FontAsset::Load(U"RuleText");

	AudioAsset::Load(U"BGM");
	AudioAsset::Load(U"Button");
	AudioAsset::Load(U"Cancel");
	AudioAsset::Load(U"Flip");
	AudioAsset::Load(U"Coin");

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
	manager.add<Memory>(State::Memory);
	manager.add<SelectCard>(State::SelectCard);
	manager.add<Bet>(State::Bet);
	manager.add<ShowDown>(State::ShowDown);
	manager.add<Result>(State::Result);

	//最初のシーンのフェードイン時間指定
	manager.init(State::Title, 0.5s);

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
