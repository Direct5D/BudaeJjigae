#include "GamePlayer2D.h"
#include "Debug.h"
#include "Util.h"
#include "Timer.h"
#include <cmath>


GamePlayer2D::GamePlayer2D(double _x, double _y, double _speed) : GameObject2D(_x, _y, _speed)
{
	DEBUG_PRINTF_A("0x%p GamePlayer2D::GamePlayer2D()\n", this);
}

GamePlayer2D::~GamePlayer2D()
{
	DEBUG_PRINTF_A("0x%p GamePlayer2D::~GamePlayer2D()\n", this);
}


GamePlayer2D::STATE GamePlayer2D::GetState()
{
	return m_State;
}


void GamePlayer2D::Move(double _x, double _y)
{
	//DEBUG_PRINTF_A("0x%p GamePlayer2D::Move()\n", this);

	m_DstPosX = _x;
	m_DstPosY = _y;
	m_State = STATE::MOVE;
}


#ifdef _DEBUG
LONGLONG lastTime;
Timer gameTimer;
#endif

// Update one frame.
// _microseconds indicates how many microseconds to update.
void GamePlayer2D::Update(LONGLONG _microseconds)
{
	//DEBUG_PRINTF_A("0x%p GamePlayer2D::Update()\n", this);

	if (m_State == STATE::MOVE)
	{
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
			m_State = STATE::STOP;
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

#ifdef _DEBUG
		LONGLONG currentTime = gameTimer.GetMicroseconds();
		if (lastTime + (0.1 * (LONGLONG)1000 * 1000) < currentTime)
		{
			DEBUG_PRINTF_A("0x%p GamePlayer::Update m_x = %f, m_Y = %f\n", this, m_X, m_Y);
			lastTime = currentTime;
		}
#endif
	}
}


GameObject* GamePlayer2D::Simulate(LONGLONG _microseconds)
{
	//DEBUG_PRINTF_A("0x%p GamePlayer2D::Simulate()\n", this);

	double x = m_X;
	double y = m_Y;

	if (m_State == STATE::MOVE)
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

	GamePlayer2D* simulatedGamePlayerPtr = new GamePlayer2D(x, y, m_Speed);
	return simulatedGamePlayerPtr;
}
