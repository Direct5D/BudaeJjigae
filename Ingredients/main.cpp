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
	double playerSpeed = 300.0;
	LPCWSTR wndName = L"Window";
	LPCWSTR wndClassName = L"Window Class";

	// Register the window class.
	WNDCLASSW wc = { };
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = BudaeJjigae::BujjiWndProc;
	wc.hInstance = _hInstance;
	wc.lpszClassName = wndClassName;
	RegisterClassW(&wc);

	// Create, initialize, and run the game.
	BudaeJjigae bujji(playerSpeed);
	bujji.InitWindow(&wc, wndName, _nShowCmd);
	bujji.Run();

	int exitCode = RunMessageLoop();

	// TODO: must wait for all games to end.

	return exitCode;
}

// Run the message loop. When the loop ends, it returns an exit code.
int RunMessageLoop()
{
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
