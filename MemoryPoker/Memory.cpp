#include "Memory.hpp"
#include "Button.hpp"

//神経衰弱画面

//コンストラクタ
Memory::Memory(const InitData& init)
	: IScene{ init } { }

//更新関数
void Memory::update()
{
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

	for (int i : step(13 * 4))
	{
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
				else
				{
					//2枚目
					getData().player.setFlipPair(getData().player.getFlipPair().first, i);

					//時間計測
					getData().stopwatch.restart();
				}
			}
		}
		else
		{
			//2枚めくった->そろっているかの判定
			if (getData().cards[getData().player.getFlipPair().first].rank == getData().cards[getData().player.getFlipPair().second].rank)
			{
				//揃っている場合
				getData().player.setFlipPair(-1, -1);
				
			}
			else
			{
				//揃っていない場合
				if (getData().stopwatch.sF() > 0.5)
				{
					AudioPlay(U"Flip");
					getData().cards[getData().player.getFlipPair().first].flip();
					getData().cards[getData().player.getFlipPair().second].flip();

					getData().player.setFlipPair(-1, -1);
				}
				
			}
			
		}

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

		//カード描画
		getData().pack(getData().cards[i]).drawAt(center);
	}

	
}
