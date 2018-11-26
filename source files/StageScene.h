#pragma once

#include "Scene.h"

struct StageData;

class CStageScene : public CScene
{
private:
	const StageData* m_pCurStage;
	Image* m_pSelectImg;
	Image* m_pBackground;
	Image* m_pCantEnter;
	int m_EnemyIDCounter;

public:
	CStageScene(const StageData* _scene);

	virtual void Update(float _time);
	virtual void Draw(Graphics* _graphics);
};