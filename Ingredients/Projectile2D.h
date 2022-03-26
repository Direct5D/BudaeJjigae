#pragma once

#include "GameObject2D.h"


class Projectile2D : public GameObject2D
{
public:
	Projectile2D(double _x, double _y, double _dstPosX, double _dstPosY, double _speed);
	virtual ~Projectile2D();

private:
	double m_DstPosX;
	double m_DstPosY;

	// GameObject2D
public:
	virtual void Update(LONGLONG _microseconds) override;
	virtual GameObject* Simulate(LONGLONG _microseconds) override;
};
