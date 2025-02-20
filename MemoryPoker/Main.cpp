#include <Siv3D.hpp> // Siv3D v0.6.14
#include "Common.hpp"

void Main()
{
	//実ウィンドウ,シーンサイズ設定
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(800, 600);
	Scene::Resize(1600, 1200);

	//シーン管理用
	App manager;


	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
