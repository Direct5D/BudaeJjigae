#include "GameMain.h"
#include "Timer.h"


constexpr auto MICROSECONDS_PER_UPDATE = 1000;

namespace Bujji
{
	void ProcessInput();
	void Update();
	void Render(HWND _hMainWindow, double _frame);

	// This is the game thread procedure. It is used when creating a thread using the CreateThread function.
	// Please pass the handle of the window in which to display the game to _lpThreadParameter.
	DWORD WINAPI GameThreadProc(LPVOID _lpThreadParameter)
	{
		HWND hMainWindow = (HWND)_lpThreadParameter;

		Timer globalGameTimer;
		LONGLONG previousTime = globalGameTimer.GetMicroseconds();
		LONGLONG lagTime = 0;

		while (true)
		{
			LONGLONG currentTime = globalGameTimer.GetMicroseconds();
			LONGLONG elapsedTime = currentTime - previousTime;
			previousTime = currentTime;
			lagTime += elapsedTime;

			ProcessInput();

			while (MICROSECONDS_PER_UPDATE <= lagTime)
			{
				Update();
				lagTime -= MICROSECONDS_PER_UPDATE;
			}

			Render(hMainWindow, lagTime / MICROSECONDS_PER_UPDATE); // 0 <= (lagTime / MICROSECONDS_PER_UPDATE) < 1
		}

		return 0; // Do not use STILL_ACTIVE as it indicates that the thread is not terminated.
	}

	void ProcessInput()
	{

	}

	void Update()
	{
		// Update every MICROSECONDS_PER_UPDATE

	}

	void Render(HWND _hMainWindow, double _frame)
	{

	}
}
