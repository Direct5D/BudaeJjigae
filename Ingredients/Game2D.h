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

private:
	ID2D1Factory* m_D2DFactoryPtr;
	ID2D1HwndRenderTarget* m_D2DRenderTargetPtr;
	ID2D1SolidColorBrush* m_BrushPtr;
	std::vector<std::shared_ptr<GameObject2D>> m_GameObjectVector;
	UINT m_Width, m_Height;

public:
	virtual bool Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd) override;
	bool AddGameObject(std::shared_ptr<GameObject2D> _gameObjectPtr);
protected:
	virtual void OnResize(WPARAM _wParam, UINT _width, UINT _height) override;
private:
	virtual void Update() override;
	virtual void Render(LONGLONG _microSeconds) override;
};
