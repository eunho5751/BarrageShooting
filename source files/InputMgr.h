#pragma once

#include "Utility.h"

class CInputMgr : public Singleton<CInputMgr>
{
	friend class Singleton<CInputMgr>;

private:
	CInputMgr() = default;
	~CInputMgr() = default;

public:
	bool IsKeyPushed(int _key, int mode = 0x8000);
	bool IsMouseClicked(RECT _rect);
	bool IsMouseClicked();
	bool IsCursorInRect(RECT _rect);
	POINT GetCursorPos() const;
};

#define INPUT_MGR() CInputMgr::GetInstance()