#include "Projectile2D.h"
#include "Debug.h"
#include "Util.h"
#include <cmath>


Projectile2D::Projectile2D(double _x, double _y, double _dstPosX, double _dstPosY, double _speed) :
	GameObject2D(_x, _y, _speed),
	m_DstPosX(_dstPosX), m_DstPosY(_dstPosY)
{
	DEBUG_PRINTF_A("0x%p Projectile2D::Projectile2D()\n", this);
}

Projectile2D::~Projectile2D()
{
	DEBUG_PRINTF_A("0x%p Projectile2D::~Projectile2D()\n", this);
}


void Projectile2D::Update(LONGLONG _microseconds)
{
	//DEBUG_PRINTF_A("0x%p Projectile2D::Update()\n", this);

	double dstX = (double)m_DstPosX;
	double dstY = (double)m_DstPosY;

	double deltaX = (dstX - m_X);
	double deltaY = (dstY - m_Y);

	double moveableDistance;
	moveableDistance = m_Speed * _microseconds;
	moveableDistance /= ((LONGLONG)1000 * 1000);

	double squaredHypotenuse = (deltaX * deltaX) + (deltaY * deltaY);

	if (squaredHypotenuse <= moveableDistance * moveableDistance)
	{
		m_X = dstX;
		m_Y = dstY;
		Destroy();
	}
	else
	{
		double distance = sqrt(squaredHypotenuse);

		if (Util::IsValidNumber(deltaX / distance) && Util::IsValidNumber(deltaY / distance))
		{
			m_X += moveableDistance * (deltaX / distance);
			m_Y += moveableDistance * (deltaY / distance);
		}
	}
}

GameObject* Projectile2D::Simulate(LONGLONG _microseconds)
{
	//DEBUG_PRINTF_A("0x%p Projectile2D::Simulate()\n", this);

	double x = m_X;
	double y = m_Y;

	{
		double dstX = (double)m_DstPosX;
		double dstY = (double)m_DstPosY;

		double deltaX = (dstX - x);
		double deltaY = (dstY - y);

		double moveableDistance;
		moveableDistance = m_Speed * _microseconds;
		moveableDistance /= ((LONGLONG)1000 * 1000);

		double squaredHypotenuse = (deltaX * deltaX) + (deltaY * deltaY);

		if (squaredHypotenuse <= moveableDistance * moveableDistance)
		{
			x = dstX;
			y = dstY;
		}
		else
		{
			double distance = sqrt(squaredHypotenuse);

			if (Util::IsValidNumber(deltaX / distance) && Util::IsValidNumber(deltaY / distance))
			{
				x += moveableDistance * (deltaX / distance);
				y += moveableDistance * (deltaY / distance);
			}
		}
	}

	Projectile2D* simulatedProjectilePtr = new Projectile2D(x, y, m_DstPosX, m_DstPosY, m_Speed);
	return simulatedProjectilePtr;
}
