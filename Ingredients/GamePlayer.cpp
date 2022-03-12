#include "GamePlayer.h"
#include "Debug.h"
#include "Util.h"
#include "Timer.h"
#include <cmath>


GamePlayer::GamePlayer(double _x, double _y, double _speed) : GameObject(_x, _y)
{
	m_Speed = _speed;
	m_State = STATE::STOP;
	m_MovePosX = 0.0;
	m_MovePosY = 0.0;
}

GamePlayer::~GamePlayer()
{

}

#ifdef _DEBUG
LONGLONG lastTime;
Timer gameTimer;
#endif

// Update one frame.
// _microseconds indicates how many microseconds to update.
void GamePlayer::Update(LONGLONG _microseconds)
{
	if (m_State == STATE::MOVE)
	{
		double moveX = (double)m_MovePosX;
		double moveY = (double)m_MovePosY;

		double deltaX = (moveX - m_X);
		double deltaY = (moveY - m_Y);

		double movDistance;
		movDistance = m_Speed * _microseconds;
		movDistance /= (1000 * 1000);

		double squaredHypotenuse = (deltaX * deltaX) + (deltaY * deltaY);

		if (squaredHypotenuse <= movDistance * movDistance)
		{
			m_X = moveX;
			m_Y = moveY;
			m_State = STATE::STOP;
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
		if (lastTime + (1000 * 1000 * 0.1) < currentTime)
		{
			DEBUG_PRINTF_A("GamePlayer::Update m_x:%f, m_Y:%f\n", m_X, m_Y);
			lastTime = currentTime;
		}
#endif
	}
}

void GamePlayer::Move(double _x, double _y)
{
	m_MovePosX = _x;
	m_MovePosY = _y;
	m_State = STATE::MOVE;
}