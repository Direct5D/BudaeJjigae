#include <Windows.h>


bool InitWindow(HINSTANCE _hInstance, int _nShowCmd);
LRESULT CALLBACK MainWndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

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
    return msg.wParam;
}

int WINAPI wWinMain(HINSTANCE _hInstance,
                   HINSTANCE _hPrevInstance,
                   PWSTR _pCmdLine,
                   int _nShowCmd)
{
    if (false == InitWindow(_hInstance, _nShowCmd))
    {
        return 0;
    }

    return RunMessageLoop();
}

bool InitWindow(HINSTANCE _hInstance, int _nShowCmd)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = _hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (0 == RegisterClassW(&wc))
    {
        return false;
    }

    HWND hMainWindow = CreateWindowW(L"Sample Window Class", L"Sample Window", WS_OVERLAPPEDWINDOW,
                                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                     NULL, NULL, _hInstance, NULL);
    if (NULL == hMainWindow)
    {
        return false;
    }

    ShowWindow(hMainWindow, _nShowCmd);
    UpdateWindow(hMainWindow);
    return true;
}

LRESULT CALLBACK MainWndProc(
    HWND _hWnd,
    UINT _uMsg,
    WPARAM _wParam,
    LPARAM _lParam)
{
    switch (_uMsg)
    {
        case WM_CREATE:
            // initialize the window. 
            return 0;

        //case WM_PAINT:
        //    // Paint the window's client area. 
        //    return 0;

        case WM_SIZE:
            // Set the size and position of the window. 
            return 0;

        case WM_CLOSE:
        {
            const int result = MessageBoxW(_hWnd, L"Are you sure you want to quit the program?", L"Warning", MB_YESNO);

            switch (result)
            {
                case IDYES:
                    PostQuitMessage(0);
                    break;
                case IDNO:
                default:
                    // Do something
                    break;
            }

            return 0;
        }

        //case WM_DESTROY:
        //    PostQuitMessage(0);
        //    return 0;

        default:
            return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
    }
    return 0;
}