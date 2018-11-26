#pragma once

#include "Scene.h"

struct StageData;

class CGameScene : public CScene
{
private:
	const StageData* m_pStage;
	float m_fElapsedTime;
	bool m_bIsGameStatred;
	Image* m_pClockImg;
	Image* m_pGaugeBarShape;
	Image* m_pGaugeBar;
	Image* m_pStageProfile;
	float m_ScrollY;

public:
	CGameScene(const StageData* _stage);
	~CGameScene();

	virtual void Update(float _time);
	virtual void Draw(Graphics* _graphics);
};