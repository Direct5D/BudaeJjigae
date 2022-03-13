#pragma once

#include "Game.h"
#include <Windows.h>
#include <vector>
#include <memory>
#include "GameObject2D.h"


class Game2D : public Game
{
public:
	Game2D();
	virtual ~Game2D();

private:
	std::vector<std::shared_ptr<GameObject2D>> m_GameObjectVector;

public:
	bool AddGameObject(std::shared_ptr<GameObject2D> _gameObjectPtr);
private:
	virtual void Update() override;
	virtual void Render(LONGLONG _microSeconds) override;
};
