#include "SelectCard.hpp"
#include "../../Button/Button.hpp"

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
		AudioPlay(U"Button", getData().SoundVolume);
		getData().NowScene = U"SelectCard";
		changeScene(State::Config, getData().changeSec);
	}
	else if (RecommendButton.leftClicked())
	{
		AudioPlay(U"Button", getData().SoundVolume);
		getData().player.RecommendRole(getData().cards);
	}
	else if (OkButton.leftClicked() && getData().player.getSelectCards().size() == 3)
	{
		//次のシーン(Betシーン)へ
		AudioPlay(U"Button", getData().SoundVolume);

		//CPUは自動で一番強い役を作成させる
		getData().cpu.RecommendRole(getData().cards);
		getData().cpu.setRoleText(getData().cards);

		//前ラウンドのBetシーンの状態をリセットしておく
		//ForNextRoundでリセットFoldがtrueだった場合選択手札の背景が一瞬白色になってしまう
		getData().cpu.setFold(false);
		getData().cpu.setActionText(U"");
		getData().player.setFold(false);
		getData().player.setActionText(U"");

		//ストップウォッチリスタート
		getData().stopwatch.restart();

		changeScene(State::Bet, getData().changeSec);
	}

	//カード選択
	for (int i = 0; i < getData().player.getHands().size(); i++)
	{
		const Vec2 center{ 575 + i % 13 * 90, 1050 };

		if (getData().pack.regionAt(center).mouseOver() && (getData().player.getSelectCards().size() < 3 || getData().player.getSelectCards().contains(getData().player.getHands()[i])))
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (getData().pack.regionAt(center).leftClicked() && (getData().player.getSelectCards().size() < 3 || getData().player.getSelectCards().contains(getData().player.getHands()[i])))
		{
			AudioPlay(U"Button", getData().SoundVolume);

			if (getData().player.getSelectCards().contains(getData().player.getHands()[i]))
			{
				//選択を解除する処理
				getData().player.removeFromSelectCards(getData().player.getHands()[i]);
			}
			else
			{
				//選択カードに追加する処理
				getData().player.insertSelectCards(getData().player.getHands()[i]);
			}
		}
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

		//選択されているカードの可視化
		if (getData().player.getSelectCards().contains(getData().player.getHands()[i]))
		{
			Rect{ 530 + i * 90, 985, 90, 130 }.drawFrame(5, Palette::Yellow);
		}
	}

	//選択したカードの表示
	RoleNameArea.draw(Palette::White);
	RoleNameArea.drawFrame(2, 2, Palette::Black);
	SelectCardArea.draw(Palette::White);
	SelectCardArea.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"選択したカード").drawAt(800, 710, Palette::Black);
	getData().player.setRoleText(getData().cards);
	FontAsset(U"Text")(getData().player.getRoleText()).drawAt(800, 600, Palette::Black);

	for (int i = 0; i < getData().player.getSelectCards().size(); i++)
	{
		const Vec2 center{ 710 + i * 90, 840 };
		getData().pack(getData().cards[getData().player.getSelectCards()[i]]).drawAt(center);
	}

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
