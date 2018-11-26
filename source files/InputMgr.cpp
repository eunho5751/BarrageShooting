#include "PCH.h"
#include "Game.h"
#include "InputMgr.h"

bool CInputMgr::IsKeyPushed(int _key, int mode)
{
	return (GetAsyncKeyState(_key) & (mode)) != 0;
}

bool CInputMgr::IsMouseClicked(RECT _rect)
{
	return IsMouseClicked() && IsCursorInRect(_rect);
}

bool CInputMgr::IsMouseClicked()
{
	return IsKeyPushed(VK_LBUTTON);
}

bool CInputMgr::IsCursorInRect(RECT _rect)
{
	POINT pos = GetCursorPos();

	return pos.x >= _rect.left && pos.x <= _rect.right && pos.y >= _rect.top && pos.y <= _rect.bottom;
}

POINT CInputMgr::GetCursorPos() const
{
	POINT pos;
	::GetCursorPos(&pos);
	ScreenToClient(GAME::GetWindow(), &pos);

	return pos;
}
