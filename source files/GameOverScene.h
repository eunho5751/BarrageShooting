#pragma once

#include "Scene.h"

struct StageData;

class CGameOverScene : public CScene
{
private:
	Image* m_pGameOver;
	const StageData* m_pStage;

public:
	CGameOverScene(const StageData* _stage);

	virtual void Update(float _time);
	virtual void Draw(Graphics* _graphics);
};