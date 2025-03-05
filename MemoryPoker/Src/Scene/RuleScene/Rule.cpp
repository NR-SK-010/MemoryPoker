#include "Rule.hpp"
#include "../../Button/Button.hpp"

//ルール画面

//コンストラクタ
//メンバ初期化リストを使用
Rule::Rule(const InitData& init)
	: IScene{ init } { }

//更新関数
void Rule::update()
{
	if (ExitButton.leftClicked())
	{
		//「戻る」
		AudioAsset(U"Cancel").play();
		if (getData().ConfigFlg)
		{
			getData().ConfigFlg = false;
			changeScene(State::Config, getData().changeSec);
		}
		else
		{
			if (getData().NowScene == U"Title")
			{
				changeScene(State::Title, getData().changeSec);
			}
		}
		
	}

	if ((ToNextPageButton.mouseOver() && page + 1 <= 7) || (ToPrePageButton.mouseOver() && page - 1 >= 1))
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (ToNextPageButton.leftClicked() && page + 1 <= 7)
	{
		AudioPlay(U"Flip");
		page++;
	}

	if (ToPrePageButton.leftClicked() && page - 1 >= 1)
	{
		AudioPlay(U"Flip");
		page--;
	}


}

//描画関数
void Rule::draw() const
{
	Scene::SetBackground(Palette::White);
	ImageArea.drawFrame(0, 8, Palette::Black);
	TextArea.draw(Palette::White);
	TextArea.drawFrame(3, 3, Palette::Black);
	Button(ExitButton, FontAsset(U"Button"), U"戻る", Palette::Black);

	FontAsset(U"RuleText")(U"{} / 7"_fmt(page)).drawAt(1480, 1100, Palette::Black);
	TriangleButton(ToNextPageButton, page + 1 <= 7);
	TriangleButton(ToPrePageButton, page - 1 >= 1);

	switch (page)
	{
	case 1:
		TextureAsset(U"Start").fitted(ImageArea.size).drawAt(ImageArea.center());
		FontAsset(U"RuleText")(U"まず、神経衰弱を行う際の先攻、後攻を選びます。").drawBase(60, 1010, Palette::Black);
		FontAsset(U"RuleText")(U"1ラウンドごとに先攻、後攻は入れ替わります。").drawBase(60, 1060, Palette::Black);
		break;
	case 2:
		TextureAsset(U"MemoryGame").fitted(ImageArea.size).drawAt(ImageArea.center());
		FontAsset(U"RuleText")(U"PlayerまたはCPUが3ペア（6枚）揃えるまで神経衰弱を行います。").drawBase(60, 1010, Palette::Black);
		FontAsset(U"RuleText")(U"2枚めくるごとに交代します。CPUが選んだカードは場所だけ分かるようになっています。").drawBase(60, 1060, Palette::Black);
		FontAsset(U"RuleText")(U"揃えたカードはCPUは画面上側中央、Playerは下側中央に移動します。").drawBase(60, 1110, Palette::Black);
		FontAsset(U"RuleText")(U"また、Playerが先に3ペア揃えるとCPUの不足分のペアとして何が追加されたかを確認できます。").drawBase(60, 1160, Palette::Black);
		break;
	case 3:
		TextureAsset(U"Select").fitted(ImageArea.size).drawAt(ImageArea.center());
		FontAsset(U"RuleText")(U"揃えた6枚のカードから、3枚選んで役を作ります。").drawBase(60, 1010, Palette::Black);
		FontAsset(U"RuleText")(U"3枚選ぶと画面中央付近の空欄に現在作られている役が表示されます。").drawBase(60, 1060, Palette::Black);
		FontAsset(U"RuleText")(U"カードをクリックすると役に加わります。もう一度クリックすると選択を解除できます。").drawBase(60, 1110, Palette::Black);
		FontAsset(U"RuleText")(U"「おすすめ」ボタンを押すと、今作れる最も強い役を自動で作ります。").drawBase(60, 1160, Palette::Black);
		break;
	case 4:
		TextureAsset(U"Bet").fitted(ImageArea.size).drawAt(ImageArea.center());
		FontAsset(U"RuleText")(U"ベットするチップの枚数を決定します。").drawBase(60, 1010, Palette::Black);
		FontAsset(U"RuleText")(U"神経衰弱で先攻だったほうが最初のベットを行います。").drawBase(60, 1060, Palette::Black);
		FontAsset(U"RuleText")(U"ベットする際の最低額は1枚、最高額は100枚です。").drawBase(60, 1110, Palette::Black);
		break;
	case 5:
		TextureAsset(U"CallRaise").fitted(ImageArea.size).drawAt(ImageArea.center());
		FontAsset(U"RuleText")(U"ベット後は交互にコール、レイズ、フォールドのどれを行うかを選択します。").drawBase(60, 1010, Palette::Black);
		FontAsset(U"RuleText")(U"どちらかがコール、またはフォールドするまでこのフェーズは続きます。").drawBase(60, 1060, Palette::Black);
		FontAsset(U"RuleText")(U"レイズする際は相手の合計ベット額よりも多くチップをベットする必要があります。").drawBase(60, 1110, Palette::Black);
		FontAsset(U"RuleText")(U"また、レイズ時のチップの上限は現在所持しているチップの枚数までです。").drawBase(60, 1160, Palette::Black);
		break;
	case 6:
		TextureAsset(U"ShowDown").fitted(ImageArea.size).drawAt(ImageArea.center());
		FontAsset(U"RuleText")(U"ショーダウンを行います。").drawBase(60, 1010, Palette::Black);
		FontAsset(U"RuleText")(U"画面上側にCPU、下側にPlayerの選んだカードと役が表示されます。").drawBase(60, 1060, Palette::Black);
		FontAsset(U"RuleText")(U"ラウンドの勝者へチップが移動した後、「次へ」を押すと次のラウンドに移行します。").drawBase(60, 1110, Palette::Black);
		FontAsset(U"RuleText")(U"これを4ラウンド繰り返します。").drawBase(60, 1160, Palette::Black);
		break;
	case 7:
		TextureAsset(U"Config").fitted(ImageArea.size).drawAt(ImageArea.center());
		FontAsset(U"RuleText")(U"プレイ中も画面右上の「メニュー」からメニューを開けます。").drawBase(60, 1010, Palette::Black);
		FontAsset(U"RuleText")(U"メニューでは音量設定や遊び方が確認できます。「テスト」を押すと効果音のサウンドテストが行えます。").drawBase(60, 1060, Palette::Black);
		break;
	default:
		break;
	}
}
