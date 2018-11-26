#pragma once

#include "Scene.h"

struct StageData;

class CGameClearScene : public CScene
{
private:
	Image* m_pGameClear;
	const StageData* m_pStage;

public:
	CGameClearScene(const StageData* _stage);

	virtual void Update(float _time);
	virtual void Draw(Graphics* _graphics);
};