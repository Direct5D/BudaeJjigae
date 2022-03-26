#pragma once

#include "Game.h"
#include <Windows.h>
#include <d2d1.h>
#include <vector>
#include <memory>
#include "GameObject2D.h"


class Game2D : public Game
{
public:
	Game2D();
	virtual ~Game2D();

protected:
	ID2D1HwndRenderTarget* m_D2DRenderTargetPtr = nullptr;
private:
	ID2D1Factory* m_D2DFactoryPtr = nullptr;
	std::vector<std::shared_ptr<GameObject2D>> m_GameObjectVector;
	//UINT m_WindowWidth = 0;
	//UINT m_WindowHeight = 0;

public:
	bool AddGameObject(std::shared_ptr<GameObject2D> _gameObjectPtr);
private:
	void ReleaseD2DRenderTarget();

protected:
	//virtual void OnWindowResize(WPARAM _wParam, UINT _width, UINT _height);
	virtual void RenderD2D(LONGLONG _lagTime);
private:
	virtual void ReleaseD2DResources() = 0;

	// Game
private:
	virtual bool OnInit() override;
	virtual void FixedUpdate() final override;
	virtual void Render(LONGLONG _lagTime) final override;
	virtual void OnTerminate() override;
};
