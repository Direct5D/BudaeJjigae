#pragma once

#include "GameObject2D.h"


class Wall2D : GameObject2D
{
public:
	Wall2D(double _x, double _y);
	virtual ~Wall2D();

public:
	virtual void Update(LONGLONG _microseconds) override;
	virtual GameObject* Simulate(LONGLONG _microseconds) override;
};
