#pragma once

#include <Windows.h>
#include <vector>
#include <memory>
#include "GameObject.h"


class Game
{
public:
	Game();
	virtual ~Game();

protected:
	HWND m_WindowHandle;
	HANDLE m_ThreadHandle;
private:
	bool m_ExitThreadFlag;
	std::vector<std::shared_ptr<GameObject>> m_GameObjectVector;

public:
	bool InitWindow(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd);
	bool Run();
	virtual void OnRightClick(WORD _x, WORD _y) = 0;
protected:
	bool AddGameObject(std::shared_ptr<GameObject> _gameObjectPtr);
private:
	void ProcessInput();
	void Update();
	void Render(double _frame);

public:
	static DWORD(WINAPI GameThreadProc)(LPVOID _lpThreadParameter);
};
