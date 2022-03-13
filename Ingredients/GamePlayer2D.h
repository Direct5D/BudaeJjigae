#pragma once

#include <Windows.h>
#include "GameObject2D.h"


class GamePlayer2D : public GameObject2D
{
public:
	GamePlayer2D(double _x, double _y, double _speed);
	virtual ~GamePlayer2D();

protected:
	enum class STATE
	{
		STOP,
		MOVE
	};

protected:
	STATE m_State;
	double m_MovePosX;
	double m_MovePosY;

public:
	virtual void Update(LONGLONG _microsecondsPerUpdate) override;
	virtual void Move(double _x, double _y);
};
