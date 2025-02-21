#include <Siv3D.hpp> // Siv3D v0.6.14
#include "Common.hpp"
#include "Title.hpp"

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

	//アセット事前ロード
	FontAsset::Load(U"Title");
	FontAsset::Load(U"Button");
	FontAsset::Load(U"Text");

	AudioAsset::Load(U"BGM");
	AudioAsset::Load(U"button");
	AudioAsset::Load(U"cancel");
	AudioAsset::Load(U"flip");
	AudioAsset::Load(U"coin");

	//シーン管理用
	App manager;
	manager.add<Title>(State::Title);

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
