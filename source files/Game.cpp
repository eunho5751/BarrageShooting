#include "PCH.h"
#include "Game.h"
#include "ResourceMgr.h"
#include "DataMgr.h"
#include "SceneMgr.h"

HWND CGame::s_HWND;

void CGame::Initialize(HWND _hWnd)
{
	//�ڵ� �ʱ�ȭ
	s_HWND = _hWnd;

	//�Ŵ��� �ʱ�ȭ
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
	//����� Scene�� �ִٸ� �ش� Scene���� �ٲ۴�.
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
