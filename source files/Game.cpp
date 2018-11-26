#include "PCH.h"
#include "Game.h"
#include "ResourceMgr.h"
#include "DataMgr.h"
#include "SceneMgr.h"

HWND CGame::s_HWND;

void CGame::Initialize(HWND _hWnd)
{
	//핸들 초기화
	s_HWND = _hWnd;

	//매니저 초기화
	RESOURCE_MGR();
	DATA_MGR();
	SCENE_MGR();
}

void CGame::Release()
{
	RESOURCE_MGR().Clear();
}

void CGame::Update(float _time)
{
	SCENE_MGR().Update(_time);
	//예약된 Scene이 있다면 해당 Scene으로 바꾼다.
	if(SCENE_MGR().GetReserveScene())
		SCENE_MGR().ChangeScene();
}

void CGame::Draw(Graphics* _graphics)
{
	SCENE_MGR().Draw(_graphics);
}

HWND CGame::GetWindow()
{
	return s_HWND;
}

void CGame::Destroy(LPCWSTR _caption, LPCWSTR _msg, UINT _type)
{
	if (lstrcmp(_msg, L"") != 0)
		MessageBox(s_HWND, _msg, _caption, _type);
	DestroyWindow(s_HWND);
}
