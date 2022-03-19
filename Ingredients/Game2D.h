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
	ID2D1Factory* m_D2DFactoryPtr = nullptr;
	ID2D1HwndRenderTarget* m_D2DRenderTargetPtr = nullptr;
	ID2D1SolidColorBrush* m_D2DBlackBrushPtr = nullptr;
	ID2D1SolidColorBrush* m_D2DGreenBrushPtr = nullptr;
	std::vector<std::shared_ptr<GameObject2D>> m_GameObjectVector;
	//UINT m_WindowWidth = 0;
	//UINT m_WindowHeight = 0;

public:
	virtual bool Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd) override;
	bool AddGameObject(std::shared_ptr<GameObject2D> _gameObjectPtr);
protected:
	virtual void OnWindowResize(WPARAM _wParam, UINT _width, UINT _height) override;
private:
	virtual void OnRButtonDown(WORD _x, WORD _y) = 0;
	virtual void OnRButtonUp(WORD _x, WORD _y) = 0;
	virtual void ProcessInput() = 0;
	virtual void Update() override;
	virtual void Render(LONGLONG _lagTime) override;
	virtual void OnTerminate() override;
	virtual void ReleaseD2DRenderTarget();
	static ID2D1SolidColorBrush* CreateD2DBrush(ID2D1HwndRenderTarget* _renderTargetPtr, CONST D2D1_COLOR_F& _colorF);
};
