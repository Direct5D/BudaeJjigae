#include <Windows.h>


int RunMessageLoop();
LRESULT CALLBACK MainWndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
void MainWndOnResize(HWND _hWnd, UINT _width, UINT _height);

int WINAPI wWinMain(_In_ HINSTANCE _hInstance,
					_In_opt_ HINSTANCE _hPrevInstance,
					_In_ LPWSTR _lpCmdLine,
					_In_ int _nShowCmd
)
{
	// Register the main window class.
	const wchar_t mainWndClassName[] = L"Main Window Class";
	const wchar_t mainWndName[] = L"Main Window";

	WNDCLASS wc = { };
	wc.lpfnWndProc = MainWndProc;
	wc.hInstance = _hInstance;
	wc.lpszClassName = mainWndClassName;

	if (0 == RegisterClassW(&wc))
		return 0;

	// Create the main window.
	HWND hMainWindow = CreateWindowW(mainWndClassName, mainWndName, WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX),
									 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
									 NULL, NULL, _hInstance, NULL);
	if (NULL == hMainWindow)
		return 0;

	ShowWindow(hMainWindow, _nShowCmd);
	UpdateWindow(hMainWindow);

	return RunMessageLoop();
}

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
			DispatchMessageW(&msg);
		}
	}

	// The exit code given in the PostQuitMessage function.
	return (int)msg.wParam;
}

LRESULT CALLBACK MainWndProc(
	HWND _hWnd,
	UINT _uMsg,
	WPARAM _wParam,
	LPARAM _lParam)
{
	switch (_uMsg)
	{
		//case WM_CREATE:
		//	// initialize the window. 
		//	return 0;

		case WM_PAINT:
		{
			// An application should not call BeginPaint except in response to a WM_PAINT message.
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(_hWnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			// Each call to BeginPaint must have a corresponding call to the EndPaint function.
			EndPaint(_hWnd, &ps);

			return 0;
		}

		// The window size has changed.
		case WM_SIZE:
		{
			UINT width = LOWORD(_lParam);
			UINT height = HIWORD(_lParam);

			MainWndOnResize(_hWnd, width, height);

			return 0;
		}

		// The user closed an application window by clicking the Close button, or by using a keyboard shortcut such as ALT + F4.
		case WM_CLOSE:
		{
			const int result = MessageBoxW(_hWnd, L"Are you sure you want to quit?", L"Warning", MB_YESNO);
			if (IDYES != result)
				return 0; // Do nothing.

			// DefWindowProc automatically calls DestroyWindow.
			// DestroyWindow destroys the window and sends WM_DESTROY and WM_NCDESTROY messages
			break;
		}

		// The window is being destroyed.
		// This message is sent after the window is removed from the screen.
		case WM_DESTROY:
		{
			// Posts a WM_QUIT message to the thread's message queue.
			PostQuitMessage(0);

			return 0;
		}

		default:
			break;
	}

	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}

void MainWndOnResize(HWND _hWnd, UINT _width, UINT _height)
{

}
