#include "SelectCard.hpp"
#include "Button.hpp"

//手札から3枚選んで役を作る

//コンストラクタ
SelectCard::SelectCard(const InitData& init)
	: IScene{ init } { };

void SelectCard::update()
{

}

void SelectCard::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);
}
