#pragma once

#include <Windows.h>
#include "GameObject.h"


class GamePlayer : public GameObject
{
public:
	GamePlayer(double _x, double _y, double _speed);
	virtual ~GamePlayer();

protected:
	double m_Speed;
	STATE m_State;
	double m_MovePosX;
	double m_MovePosY;

public:
	virtual void Update(LONGLONG _microsecondsPerUpdate) override;
	virtual void Move(double _x, double _y);
};
