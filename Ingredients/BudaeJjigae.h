#pragma once

#include "Game.h"
#include "GamePlayer.h"
#include <memory>


class BudaeJjigae : public Game
{
public:
	BudaeJjigae(double _speed);
	virtual ~BudaeJjigae();

private:
	std::shared_ptr<GamePlayer> m_PlayerPtr;

public:
	virtual void OnRightClick(WORD _x, WORD _y);
};
