#include <Windows.h>
#include "Debug.h"
#include "BudaeJjigae.h"


int RunMessageLoop();

int WINAPI wWinMain(_In_ HINSTANCE _hInstance,
					_In_opt_ HINSTANCE _hPrevInstance,
					_In_ LPWSTR _lpCmdLine,
					_In_ int _nShowCmd
)
{
	DEBUG_PRINTF_A("wWinMain()\n");

	double playerSpeed = 300.0;
	LPCWSTR wndName = L"Window";
	LPCWSTR wndClassName = L"Window Class";

	// Register the window class.
	WNDCLASSW wc = { };
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = BudaeJjigae::BujjiWndProc;
	wc.hInstance = _hInstance;
	wc.lpszClassName = wndClassName;
	if (0 == RegisterClassW(&wc))
		return 0;

	// Create and initialize the game.
	BudaeJjigae bujji(playerSpeed);

	if (false == bujji.Init(&wc, wndName, _nShowCmd))
		return 0;

	// TODO: Terminates the game's own message loop and game procedures when the game window is destroyed.
	int exitCode = RunMessageLoop();

	bujji.TerminateThread();

	return exitCode;
}

// Run the message loop. When the loop ends, it returns an exit code.
int RunMessageLoop()
{
	DEBUG_PRINTF_A("RunMessageLoop()\n");

	BOOL bRet;
	MSG msg;

	// If the GetMessage retrieves the WM_QUIT message, the return value is zero.
	while (0 != (bRet = GetMessageW(&msg, NULL, 0, 0)))
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg); // Dispatch the message to the target window.
		}
	}

	// The exit code given in the PostQuitMessage function.
	return (int)msg.wParam;
}
