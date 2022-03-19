#pragma once

#include <Windows.h>
#include "GameObject2D.h"


class GamePlayer2D : public GameObject2D
{
public:
	GamePlayer2D(double _x, double _y, double _speed);
	virtual ~GamePlayer2D();

public:
	enum class STATE
	{
		STOP,
		MOVE
	};

protected:
	STATE m_State = STATE::STOP;
	double m_MovePosX = 0.0;
	double m_MovePosY = 0.0;

public:
	STATE GetState();

public:
	virtual void Update(LONGLONG _microsecondsPerUpdate) override;
	virtual void Move(double _x, double _y);
	virtual void SimulatePos(LONGLONG _microseconds, double& _outX, double& _outY);
};
