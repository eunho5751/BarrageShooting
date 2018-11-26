#pragma once

#include "Utility.h"

class CScene;

class CSceneMgr : public Singleton<CSceneMgr>
{
	friend class Singleton<CSceneMgr>;

private:
	CScene *m_pCurScene, *m_pNextScene;

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Update(float _time);
	void Draw(Graphics* graphics);

	void ChangeScene();
	void ReserveScene(CScene* _scene);
	const CScene* GetCurScene() const;
	const CScene* GetReserveScene() const;
};

#define SCENE_MGR() CSceneMgr::GetInstance()