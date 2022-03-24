#include "GameObject.h"
#include "Debug.h"


GameObject::GameObject(double _speed)
{
	DEBUG_PRINTF_A("0x%p GameObject::GameObject()\n", this);
	m_Speed = _speed;
}

GameObject::~GameObject()
{
	DEBUG_PRINTF_A("0x%p GameObject::~GameObject()\n", this);
}


bool GameObject::GetValid()
{
	// TODO: Find out what is causing the "this was nullptr" exception sometimes.
	return m_Valid;
}

double GameObject::GetSpeed()
{
	return m_Speed;
}

void GameObject::Destroy()
{
	m_Valid = false;
}
