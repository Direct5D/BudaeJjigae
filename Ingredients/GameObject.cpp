#include "GameObject.h"
#include "Debug.h"


GameObject::GameObject(double _speed)
{
	DEBUG_PRINTF_A("GameObject::GameObject()\n");
	m_Speed = _speed;
}

GameObject::~GameObject()
{
	DEBUG_PRINTF_A("GameObject::~GameObject()\n");
}
