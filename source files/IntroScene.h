#pragma once

#include "Scene.h"

class CIntroScene : public CScene
{
private:
	Image* m_pIntroTitle;
	Image* m_pBackground;
	Image *m_pStartButton, *m_pStartOnButton;
	Image* m_pCurButton;
	RECT m_StartButtonRect;
	bool m_bStartButtonClicked;
	POINT m_StartButtonClickedPoint;
	float m_fElapsedTime;
	bool m_bCursorInRect;

public:
	CIntroScene();

	virtual void Update(float _time);
	virtual void Draw(Graphics* graphics);
};