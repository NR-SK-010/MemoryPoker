#pragma once
#include "Common.hpp"

//ベットシーン

class Bet : public App::Scene
{
public:
	Bet(const InitData& init);

	void update() override;

	void draw() const override;

private:
	//次のシーンに行くかどうかの判定
	bool NextScene();
	//レイズ可能か
	bool CanRaise() const;

	//通常の表示
	Rect MenuButton{ Arg::center(1480, 70), 200, 80 }; //メニューボタン
	RoundRect PlayerSelectCardArea{ Arg::center(800, 950), 400, 200, 7 }; //Player選択カード表示エリア
	RoundRect PlayerNameArea{ Arg::center(1250, 865), 200, 70, 7 }; //PlayerName表示エリア
	RoundRect PlayerChipArea{ Arg::center(1350, 1100), 400, 100, 7 }; //PlayerChip表示エリア
	RoundRect PlayerBetArea{ Arg::center(1350, 970), 400, 100, 7 }; //PlayerBet額表示エリア
	RoundRect PlayerActionArea{ Arg::center(1350, 700), 400, 100, 7 }; //「コール」or「レイズ」or「フォールド」(Playerが選択した行動)の表示

	Rect CallButton{ Arg::center(300, 840), 550, 100 }; //「コール」ボタン
	Rect ToRaiseButton{ Arg::center(300, 970), 550, 100 }; //「レイズ」ボタン(レイズ額決定メニューを表示させる)
	Rect FoldButton{ Arg::center(300, 1100), 550, 100 }; //「フォールド」ボタン

	RoundRect CpuSelectCardArea{ Arg::center(800, 250), 400, 200, 7 }; //CPU選択カード表示エリア
	RoundRect CpuNameArea{ Arg::center(150, 90), 200, 70, 7 }; //CPUName表示エリア
	RoundRect CpuChipArea{ Arg::center(250, 315), 400, 100, 7 }; //CpuChip表示エリア
	RoundRect CpuBetArea{ Arg::center(250, 195), 400, 100, 7 }; //CpuBet額表示エリア
	RoundRect CpuActionArea{ Arg::center(250, 500), 400, 100, 7 }; //「コール」or「レイズ」or「フォールド」(CPUが選択した行動)の表示
	
	

	RoundRect BetRaiseArea{ Arg::center(800, 600), 600, 400, 7 }; //ベット、レイズ額決定時のエリア

	//最初のベット時
	Rect BetButton{ Arg::center(800, 740), 250, 100 }; //ベット額決定ボタン

	//レイズ時のBet額決定に使う
	Rect RaiseButton{ Arg::center(640, 740), 250, 100 }; //レイズ額確定ボタン
	Rect RaiseCancelButton{ Arg::center(960, 740), 250, 100 }; //レイズキャンセル

	//「コール」、「レイズ」、「フォールド」ボタンの設定
	ColorF ButtonColor{ 0, 0.8, 1.0 }; //ボタンの色
	bool CanPress = false; //「コール」、「レイズ」、「フォールド」ボタンが押せるかどうか

	//ベット額決定時のボタン(最初のベット、レイズ時使用)
	Triangle leftButton{ 700, 550, 70, 270_deg }; //左(-10)
	Triangle rightButton{ 900, 550, 70, 90_deg }; //右(+10)
	Triangle upButton{ 800, 480, 70 }; //上(+1)
	Triangle downButton{ 800, 620, 70, 180_deg }; //下(-1)
};
