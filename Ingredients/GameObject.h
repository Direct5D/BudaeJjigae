#pragma once

#include <Windows.h>


class GameObject
{
public:
	GameObject(double _speed = 0);
	virtual ~GameObject();

protected:
	double m_Speed;

public:
	double GetSpeed();
	virtual void Update(LONGLONG _microseconds) = 0;
};
