#include "GamePlayer.h"
#include "Debug.h"
#include "Util.h"
#include "Timer.h"
#include <cmath>


GamePlayer::GamePlayer(double _x, double _y, double _speed) : GameObject(_x, _y)
{
	m_PlayerSpeed = _speed;
	m_PlayerState = STATE::STOP;
}

GamePlayer::~GamePlayer()
{

}

#ifdef _DEBUG
LONGLONG lastTime;
Timer gameTimer;
#endif

void GamePlayer::Update(LONGLONG _microseconds)
{
	if (m_PlayerState == STATE::MOVE)
	{
		double moveX = (double)m_PlayerMovePosX;
		double moveY = (double)m_PlayerMovePosY;

		double deltaX = (moveX - m_X);
		double deltaY = (moveY - m_Y);

		double movDistance;
		movDistance = m_PlayerSpeed * _microseconds;
		movDistance /= (1000 * 1000);

		double squaredHypotenuse = (deltaX * deltaX) + (deltaY * deltaY);

		if (squaredHypotenuse <= movDistance * movDistance)
		{
			m_X = moveX;
			m_Y = moveY;
			m_PlayerState = STATE::STOP;
		}
		else
		{
			double distance = sqrt(squaredHypotenuse);

			if (Util::IsValidNumber(deltaX / distance) && Util::IsValidNumber(deltaY / distance))
			{
				m_X += movDistance * (deltaX / distance);
				m_Y += movDistance * (deltaY / distance);
			}
		}

#ifdef _DEBUG
		LONGLONG currentTime = gameTimer.GetMicroseconds();
		if (lastTime + (1000 * 1000 * 0.0) < currentTime)
		{
			DEBUG_PRINTF_A("GamePlayer::Update m_x:%f, m_Y:%f\n", m_X, m_Y);
			lastTime = currentTime;
		}
#endif
	}
}

void GamePlayer::Move(double _x, double _y)
{
	m_PlayerMovePosX = _x;
	m_PlayerMovePosY = _y;
	m_PlayerState = STATE::MOVE;
}
