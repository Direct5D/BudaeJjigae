#include "BudaeJjigae.h"


BudaeJjigae::BudaeJjigae(double _speed) : Game()
{
	m_PlayerPtr = std::shared_ptr<GamePlayer>(new GamePlayer(0, 0, _speed));
	AddGameObject(m_PlayerPtr);
}

BudaeJjigae::~BudaeJjigae()
{

}


void BudaeJjigae::OnRightClick(WORD _x, WORD _y)
{
	m_PlayerPtr->Move(_x, _y);
}
