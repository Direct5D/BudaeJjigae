#include "Wall2D.h"
#include "Debug.h"


Wall2D::Wall2D(double _x, double _y) : GameObject2D(_x, _y, 0)
{
	DEBUG_PRINTF_A("0x%p Wall2D::Wall2D()\n", this);
}

Wall2D::~Wall2D()
{
	DEBUG_PRINTF_A("0x%p Wall2D::~Wall2D()\n", this);
}


void Wall2D::Update(LONGLONG _microseconds)
{
	// empty
}

GameObject* Wall2D::Simulate(LONGLONG _microseconds)
{
	Wall2D* simulatedWallPtr = new Wall2D(m_X, m_Y);
	return simulatedWallPtr;
}
