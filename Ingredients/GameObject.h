#pragma once

#include <Windows.h>


class GameObject
{
public:
	GameObject(double _speed = 0);
	virtual ~GameObject();

protected:
	bool m_Valid = true;
	double m_Speed;

public:
	bool GetValid();
	double GetSpeed();
protected:
	void Destroy();

public:
	virtual void Update(LONGLONG _microseconds) = 0;
	virtual GameObject* Simulate(LONGLONG _microseconds) = 0;
};
