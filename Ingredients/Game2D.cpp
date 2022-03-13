#include "Game2D.h"
#include "Debug.h"


Game2D::Game2D()
{
	DEBUG_PRINTF_A("Game2D::Game2D()\n");
}

Game2D::~Game2D()
{
	DEBUG_PRINTF_A("Game2D::~Game2D()\n");
}


bool Game2D::AddGameObject(std::shared_ptr<GameObject2D> _gameObjectPtr)
{
	DEBUG_PRINTF_A("Game2D::AddGameObject()\n");
	if (_gameObjectPtr == nullptr)
		return false;

	m_GameObjectVector.push_back(_gameObjectPtr);
	return true;
}


void Game2D::Update()
{
	//DEBUG_PRINTF_A("Game2D::Update()\n");
	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		m_GameObjectVector[i]->Update(MICROSECONDS_PER_UPDATE);
	}
}

void Game2D::Render(LONGLONG _microSeconds)
{
	//DEBUG_PRINTF_A("Game2D::Render()\n");
	// Render using the window handle.
	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		GameObject2D* gameObjectPtr = m_GameObjectVector[i].get();

		// Get information from a 2D game object and render it.

	}
}
