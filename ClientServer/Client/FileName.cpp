#include <iostream>
#include <winsock2.h>
#pragma warning(disable: 4996)
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#pragma comment(lib, "user32.lib") 
bool g_bKeyState[256] = { false };
bool g_bMouseState[3] = { false };
int  g_nMouseX = 0;
int  g_nMouseY = 0;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
    {
        g_bKeyState[wParam] = true;
        break;
    }

    case WM_KEYUP:
    {
        g_bKeyState[wParam] = false;
        break;
    }

    case WM_MOUSEMOVE:
    {
        g_nMouseX = LOWORD(lParam);
        g_nMouseY = HIWORD(lParam);
        break;
    }

    case WM_LBUTTONDOWN:
    {
        g_bMouseState[0] = true;
        break;
    }

    case WM_LBUTTONUP:
    {
        g_bMouseState[0] = false;
        break;
    }

    case WM_RBUTTONDOWN:
    {
        g_bMouseState[1] = true;
        break;
    }

    case WM_RBUTTONUP:
    {
        g_bMouseState[1] = false;
        break;
    }

    case WM_MBUTTONDOWN:
    {
        g_bMouseState[2] = true;
        break;
    }

    case WM_MBUTTONUP:
    {
        g_bMouseState[2] = false;
        break;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void PrintInputState()
{
    std::cout << "---- Keyboard State ----" << std::endl;
    for (int i = 0; i < 256; i++)
    {
        if (g_bKeyState[i])
        {
            std::cout << "Key " << i << " is pressed." << std::endl;
        }
    }

    std::cout << "---- Mouse State ----" << std::endl;
    std::cout << "Mouse position: (" << g_nMouseX << ", " << g_nMouseY << ")" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        if (g_bMouseState[i])
        {
            std::cout << "Mouse button " << i << " is pressed." << std::endl;
        }
    }
}
int main() {
	WSAData Data;
	WORD Version = MAKEWORD(2, 1);
	if (WSAStartup(Version, &Data) != 0) {
		std::cout << "Error";
		return 0;
	}
	SOCKADDR_IN addres;
	addres.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY
	addres.sin_port = htons(1025);
	addres.sin_family = AF_INET;
	
	SOCKET kin = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(kin, (SOCKADDR*)&addres, sizeof(addres)) == 0) {
		std::cout << "connection";
		return 0;
	}



    HWND hwnd = CreateWindowEx(
        0,
        (LPWSTR)"STATIC",
        (LPWSTR)"Keyboard and Mouse Activity Monitoring",
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        300,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    // Регистрируем функцию WindowProc как обработчик сообщений для окна
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // Запускаем бесконечный цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Выводим информацию о состоянии клавиатуры и мыши
        PrintInputState();
    }

	
	system("pause");
	return 1;
}