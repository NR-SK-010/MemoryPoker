#include "SelectCard.hpp"
#include "Button.hpp"

//手札から3枚選んで役を作る

//コンストラクタ
SelectCard::SelectCard(const InitData& init)
	: IScene{ init } { };

void SelectCard::update()
{
	if (MenuButton.mouseOver() || RecommendButton.mouseOver() || (OkButton.mouseOver() && getData().player.getSelectCards().size() == 3))
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (MenuButton.leftClicked())
	{
		AudioPlay(U"Button");
		getData().NowScene = U"SelectCard";
		changeScene(State::Config, getData().changeSec);
	}
	else if (RecommendButton.leftClicked())
	{
		AudioPlay(U"Button");
	}
	else if (OkButton.leftClicked() && getData().player.getSelectCards().size() == 3)
	{
		AudioPlay(U"Button");
	}

}

void SelectCard::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	//メニューボタン
	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);

	//Player手札表示
	PlayerHandsArea.draw(Palette::White);
	PlayerHandsArea.drawFrame(2, 2, Palette::Black);
	for (int i = 0; i < getData().player.getHands().size(); i++)
	{
		const Vec2 center{ 575 + i * 90, 1050 };
		getData().pack(getData().cards[getData().player.getHands()[i]]).drawAt(center);
	}

	//選択したカードの表示
	RoleNameArea.draw(Palette::White);
	RoleNameArea.drawFrame(2, 2, Palette::Black);
	SelectCardArea.draw(Palette::White);
	SelectCardArea.drawFrame(2, 2, Palette::Black);

	//CPU手札表示
	CpuHandsArea.draw(Palette::White);
	CpuHandsArea.drawFrame(2, 2, Palette::Black);
	for (int i = 0; i < getData().cpu.getHands().size(); i++)
	{
		const Vec2 center{ 575 + i * 90, 220 };
		getData().pack(getData().cards[getData().cpu.getHands()[i]]).drawAt(center);
	}

	Button(RecommendButton, FontAsset(U"Button"), U"おすすめ", Palette::Black);
	Button(OkButton, FontAsset(U"Button"), U"OK", Palette::Black, getData().player.getSelectCards().size() == 3);
}
