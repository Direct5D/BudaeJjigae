#pragma once

#include <Windows.h>


class GameObject
{
public:
	GameObject(double _x, double _y);
	virtual ~GameObject();

protected:
	enum class STATE
	{
		STOP,
		MOVE
	};

protected:
	double m_X, m_Y;
	
public:
	virtual void Update(LONGLONG _microseconds) = 0;
};
