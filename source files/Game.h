#pragma once

class CGame
{
private:
	static HWND s_HWND;

private:
	CGame() = default;
	~CGame() = default;

public:
	static void Initialize(HWND _hWnd);
	static void Release();

	static void Update(float _time);
	static void Draw(Graphics* _graphics);

	static HWND GetWindow();
	static void Destroy(LPCWSTR caption, LPCWSTR msg, UINT _type);
};

#define GAME CGame