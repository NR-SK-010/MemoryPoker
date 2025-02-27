#include "Memory.hpp"
#include "Button.hpp"

//神経衰弱画面

//コンストラクタ
Memory::Memory(const InitData& init)
	: IScene{ init } { }

//更新関数
void Memory::update()
{
	//メニューボタン処理
	if (MenuButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (MenuButton.leftClicked())
	{
		AudioPlay(U"Button");
		getData().NowScene = U"Memory";
		changeScene(State::Config, getData().changeSec);
	}

	//どちらかが6枚(3ペア)揃えるまで神経衰弱
	if (getData().Memory_PlayerTurn && getData().player.getHands().size() < 6 && getData().cpu.getHands().size() < 6)
	{
		//Playerの手番

		for (int i : step(13 * 4))
		{
			//UsedCards(使用済み)に含まれている場合は無視
			if (getData().UsedCards.contains(i)) continue;

			//すでにめくられているカードは無視(FlipPair1枚目はまだUsedCardsに入っていない状態)
			if (getData().player.getFlipPair().first == i) continue;

			//カードの座標
			const Vec2 center{ 260 + i % 13 * 90, 405 + (i / 13) * 130 };
			if (getData().player.getFlipPair().first == -1 || getData().player.getFlipPair().second == -1)
			{
				//二枚めくってない状態
				if (getData().pack.regionAt(center).mouseOver())
				{
					Cursor::RequestStyle(CursorStyle::Hand);
				}

				if (getData().pack.regionAt(center).leftClicked())
				{
					getData().cards[i].flip();
					AudioPlay(U"Flip");

					if (getData().player.getFlipPair().first == -1)
					{
						//1枚目
						getData().player.setFlipPair(i, -1);
					}
					//同じカードのクリックを防ぐ
					else if (getData().player.getFlipPair().first != i)
					{
						//2枚目
						getData().player.setFlipPair(getData().player.getFlipPair().first, i);

						//時間計測開始
						getData().stopwatch.restart();
					}
				}
			}
			else
			{
				//2枚めくられている状態
				//この状態を0.5s維持
				if (getData().stopwatch.sF() < 0.5) continue;

				//2枚めくった->そろっているかの判定
				if (getData().cards[getData().player.getFlipPair().first].rank == getData().cards[getData().player.getFlipPair().second].rank)
				{
					//揃っている場合

					if (!getData().UsedCards.contains(getData().player.getFlipPair().first))
					{
						//UsedCardsに情報を保存
						getData().UsedCards.insert(getData().player.getFlipPair().first);
						getData().UsedCards.insert(getData().player.getFlipPair().second);
					}
					else
					{
						if (getData().stopwatch.sF() >= 2.0)
						{
							//2.0s後(めくられた状態で0.5s,移動に1s,その後0.5s)に手札に入れる

							//手札に揃えた2枚を追加
							getData().player.push_back_Hands(getData().player.getFlipPair().first);
							getData().player.push_back_Hands(getData().player.getFlipPair().second);

							//めくったカードの情報をリセット
							getData().player.setFlipPair(-1, -1);

							//ストップウォッチリスタート
							getData().stopwatch.restart();

							//CPUのターンに回す
							getData().Memory_PlayerTurn = false;
						}
					}

				}
				else
				{
					//揃っていない場合

					//元に戻す
					getData().cards[getData().player.getFlipPair().first].flip();
					getData().cards[getData().player.getFlipPair().second].flip();

					//めくったカードの情報をリセット
					getData().player.setFlipPair(-1, -1);

					//ストップウォッチリスタート
					getData().stopwatch.restart();

					//CPUのターンに回す
					getData().Memory_PlayerTurn = false;
				}

			}

		}
	}
	else if(getData().player.getHands().size() < 6 && getData().cpu.getHands().size() < 6)
	{
		//CPUの手番

		//次の行動まで0.5s待機
		if (getData().cpu.getFlipPair().first == -1 && getData().stopwatch.sF() > 0.5)
		{
			//1枚目
			getData().cpu.setFlipPair(getData().cpu.SelectFirstCard(getData().cards, getData().UsedCards), -1);

			AudioPlay(U"Flip");

			//ストップウォッチリスタート
			getData().stopwatch.restart();
		}
		else if(getData().cpu.getFlipPair().second == -1 && getData().stopwatch.sF() > 0.5)
		{
			//2枚目
			getData().cpu.setFlipPair(getData().cpu.getFlipPair().first, getData().cpu.SelectSecondCard(getData().cards, getData().UsedCards, getData().cpu.getFlipPair().first));

			AudioPlay(U"Flip");

			//ストップウォッチリスタート
			getData().stopwatch.restart();
		}
		else if(getData().stopwatch.sF() > 0.5)
		{
			//2枚選択後
				
			//2枚めくった->そろっているかの判定
			if (getData().cards[getData().cpu.getFlipPair().first].rank == getData().cards[getData().cpu.getFlipPair().second].rank)
			{
				//揃っている場合

				if (!getData().UsedCards.contains(getData().cpu.getFlipPair().first))
				{
					//UsedCardsに情報を保存
					getData().UsedCards.insert(getData().cpu.getFlipPair().first);
					getData().UsedCards.insert(getData().cpu.getFlipPair().second);
				}
				else
				{
					if (getData().stopwatch.sF() >= 2.0)
					{
						//2.0s後(めくられた状態で0.5s,移動に1s,その後0.5s)に手札に入れる

						//手札に揃えた2枚を追加
						getData().cpu.push_back_Hands(getData().cpu.getFlipPair().first);
						getData().cpu.push_back_Hands(getData().cpu.getFlipPair().second);

						//めくったカードの情報をリセット
						getData().cpu.setFlipPair(-1, -1);

						//ストップウォッチリスタート
						getData().stopwatch.restart();

						//Playerのターンに回す
						getData().Memory_PlayerTurn = true;
					}
				}

			}
			else
			{
				//揃っていない場合

				//めくったカードの情報をリセット
				getData().cpu.setFlipPair(-1, -1);

				//ストップウォッチリスタート
				getData().stopwatch.restart();

				//Playerのターンに回す
				getData().Memory_PlayerTurn = true;
			}

		}
		
	}
	else
	{
		//どちらかが6枚(3ペア)揃えた
	}

}

//描画関数
void Memory::draw() const
{
	//背景色
	Scene::SetBackground(Palette::Green);

	//メニュー(設定)ボタン
	Button(MenuButton, FontAsset(U"Button"), U"メニュー", Palette::Black);

	//Player側情報表示
	PlayerCardsFrame.draw(Palette::White);
	PlayerCardsFrame.drawFrame(2, 2, Palette::Black);

	PlayerNameFrame.draw(Palette::White);
	PlayerNameFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().player.getName()).drawAt(1250, 995, Palette::Black);

	PlayerChipFrame.draw(Palette::White);
	PlayerChipFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"CHIP").drawAt(1250, 1100, Palette::Black);
	FontAsset(U"Text")(getData().player.getChip()).drawAt(1450, 1100, Palette::Black);



	//CPU側情報表示
	CpuCardsFrame.draw(Palette::White);
	CpuCardsFrame.drawFrame(2, 2, Palette::Black);

	CpuNameFrame.draw(Palette::White);
	CpuNameFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(getData().cpu.getName()).drawAt(150, 90, Palette::Black);

	CpuChipFrame.draw(Palette::White);
	CpuChipFrame.drawFrame(2, 2, Palette::Black);
	FontAsset(U"Text")(U"CHIP").drawAt(150, 195, Palette::Black);
	FontAsset(U"Text")(getData().cpu.getChip()).drawAt(350, 195, Palette::Black);

	//場に残っているカードの描画
	for (int i : step(13 * 4))
	{
		//カードの座標
		const Vec2 center{ 260 + i % 13 * 90, 405 + (i / 13) * 130 };

		//UsedCardsに含まれていないかチェック
		if (!getData().UsedCards.contains(i))
		{
			//場にカードを描画
			getData().pack(getData().cards[i]).drawAt(center);

			//cpuの選択カードを可視化
			if (getData().cpu.getFlipPair().first == i || getData().cpu.getFlipPair().second == i)
			{
				Rect{ 215 + i % 13 * 90, 340 + (i / 13) * 130, 90, 130 }.drawFrame(5, Palette::Yellow);
			}
		}
		
	}

	//揃えたカードの移動(Player側)
	if (getData().UsedCards.contains(getData().player.getFlipPair().first) && getData().stopwatch.sF() <= 2.0)
	{
		//イージング

		//UsedCardsに追加されるのは0.5s後(update()側で記述)
		const double t = Min(getData().stopwatch.sF() - 0.5, 1.0);
		const double e = EaseInOutExpo(t);

		//1枚目
		Vec2 pos = CardMove(Vec2{ 260 + getData().player.getFlipPair().first % 13 * 90, 405 + (getData().player.getFlipPair().first / 13) * 130 }, Vec2{ 575 + (getData().player.getHands().size()) * 90, 1050 }, e);
		getData().pack(getData().cards[getData().player.getFlipPair().first]).drawAt(pos);

		//2枚目
		pos = CardMove(Vec2{ 260 + getData().player.getFlipPair().second % 13 * 90, 405 + (getData().player.getFlipPair().second / 13) * 130 }, Vec2{ 575 + (getData().player.getHands().size() + 1) * 90, 1050 }, e);
		getData().pack(getData().cards[getData().player.getFlipPair().second]).drawAt(pos);
	}

	//揃えたカードの移動(CPU側)
	if (getData().UsedCards.contains(getData().cpu.getFlipPair().first) && getData().stopwatch.sF() <= 2.0)
	{
		//イージング

		//UsedCardsに追加されるのは0.5s後(update()側で記述)
		const double t = Min(getData().stopwatch.sF() - 0.5, 1.0);
		const double e = EaseInOutExpo(t);

		//1枚目
		Vec2 pos = CardMove(Vec2{ 260 + getData().cpu.getFlipPair().first % 13 * 90, 405 + (getData().cpu.getFlipPair().first / 13) * 130 }, Vec2{ 575 + (getData().cpu.getHands().size()) * 90, 150 }, e);
		getData().pack(getData().cards[getData().cpu.getFlipPair().first]).drawAt(pos);

		//2枚目
		pos = CardMove(Vec2{ 260 + getData().cpu.getFlipPair().second % 13 * 90, 405 + (getData().cpu.getFlipPair().second / 13) * 130 }, Vec2{ 575 + (getData().cpu.getHands().size() + 1) * 90, 150 }, e);
		getData().pack(getData().cards[getData().cpu.getFlipPair().second]).drawAt(pos);
	}

	//PlayerのHandsカード描画
	for (int32 i = 0; i < getData().player.getHands().size(); i++)
	{
		const Vec2 center{ 575 + i * 90, 1050 };
		getData().pack(getData().cards[getData().player.getHands()[i]]).drawAt(center);
	}

	//CPUのHandsカード描画
	for (int32 i = 0; i < getData().cpu.getHands().size(); i++)
	{
		const Vec2 center{ 575 + i * 90, 150 };
		getData().pack(getData().cards[getData().cpu.getHands()[i]]).drawAt(center);
	}

	
}

//イージングの際に使用
Vec2 Memory::CardMove(const Vec2 from, const Vec2 to, const double e) const
{
	return from.lerp(to, e);
}
