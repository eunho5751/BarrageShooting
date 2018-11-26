
#include "PCH.h"
#include "def.h"
#include "Game.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("201613164 최은호");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//GDI+ 초기화
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	//윈도우 초기화
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, IDC_APPSTARTING);
	WndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindowEx(0, lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

	ZeroMemory(&Message, sizeof(MSG));

	/********************************************/
	GAME::Initialize(hWnd);

	//메인 루프
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			//게임 루프
			static DWORD prev = timeGetTime();
			DWORD now = timeGetTime();

			GAME::Update((now - prev) * 0.001f);
			InvalidateRect(hWnd, nullptr, false);

			prev = now;
		}
	}

	GAME::Release();
	/********************************************/

	//GDI+ 해제
	GdiplusShutdown(gdiplusToken);

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_ERASEBKGND:
		return true;
		
	case WM_PAINT:
	{
		//double buffering
		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc, memDC;
		hdc = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hdc);
		GetClientRect(hWnd, &rect);
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		SelectObject(memDC, bitmap);
		FillRect(memDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		Graphics graphics(memDC);

		graphics.SetPixelOffsetMode(PixelOffsetModeHalf);
		graphics.SetSmoothingMode(SmoothingModeNone);
		graphics.SetInterpolationMode(InterpolationModeDefault);

		/*		Custom Draw		*/
		GAME::Draw(&graphics);
		//////////////////////////

		SelectObject(memDC, bitmap);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

		DeleteObject(bitmap);
		DeleteDC(memDC);
		EndPaint(hWnd, &ps);
	
		return 0;
	}
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
