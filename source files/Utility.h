#pragma once

template <typename T>
class Singleton
{
private:
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

protected:
	Singleton() = default;
	~Singleton() = default;

public:
	static T& GetInstance()
	{
		static T instance;

		return instance;
	}
};
/*
HBITMAP LoadFromFile(LPCTSTR lpFileName)
{
	HANDLE hFile = CreateFile(lpFileName, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return NULL;

	BITMAPFILEHEADER bmfh;
	DWORD dwRead;
	ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);

	DWORD dwInfoLength = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
	LPBITMAPINFO lpbmi = (LPBITMAPINFO)new BYTE[dwInfoLength];
	ReadFile(hFile, lpbmi, dwInfoLength, &dwRead, NULL);

	HDC hDC = GetDC(GetDesktopWindow());

	LPVOID lpDIBits;
	HBITMAP hDIB = CreateDIBSection(hDC, lpbmi, DIB_RGB_COLORS, &lpDIBits, NULL, 0);
	ReleaseDC(GetDesktopWindow(), hDC);

	ReadFile(hFile, lpDIBits, lpbmi->bmiHeader.biSizeImage, &dwRead, NULL);
	CloseHandle(hFile);

	delete[] lpbmi;

	return hDIB;
}
*/