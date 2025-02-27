#pragma once
#include "Common.hpp"

//手札から3枚選んで役を作る

class SelectCard : public App::Scene
{
public:
	SelectCard(const InitData& init);

	void update() override;

	void draw() const override;

private:

};
