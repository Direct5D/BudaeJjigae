#pragma once

#include "GameObject.h"
#include <Windows.h>


class GameObject2D : public GameObject
{
public:
	GameObject2D(double _x, double _y, double _speed);
	virtual ~GameObject2D();

protected:
	double m_X, m_Y;

public:
	double GetX();
	double GetY();
};
