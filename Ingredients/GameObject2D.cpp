#include "GameObject2D.h"
#include "Debug.h"


GameObject2D::GameObject2D(double _x, double _y, double _speed)
{
	DEBUG_PRINTF_A("GameObject2D::~GameObject2D()\n");
	m_X = _x;
	m_Y = _y;
	m_Speed = _speed;
}

GameObject2D::~GameObject2D()
{
	DEBUG_PRINTF_A("GameObject2D::~GameObject2D()\n");
}
