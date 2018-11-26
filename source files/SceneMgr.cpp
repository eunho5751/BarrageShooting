#include "PCH.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "IntroScene.h"
#include "GameScene.h"

CSceneMgr::CSceneMgr() : m_pCurScene(new CIntroScene), m_pNextScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	if (m_pCurScene != nullptr)
		delete m_pCurScene;
	if (m_pNextScene != nullptr)
		delete m_pNextScene;
}

void CSceneMgr::Update(float _time)
{
	if (m_pCurScene != nullptr)
		m_pCurScene->Update(_time);
}

void CSceneMgr::Draw(Graphics * graphics)
{
	if (m_pCurScene != nullptr)
		m_pCurScene->Draw(graphics);
}

void CSceneMgr::ChangeScene()
{
	if (m_pCurScene != nullptr)
		delete m_pCurScene;

	m_pCurScene = m_pNextScene;
	m_pNextScene = nullptr;
}

void CSceneMgr::ReserveScene(CScene* _scene)
{
	if (m_pNextScene != nullptr)
		delete m_pNextScene;

	m_pNextScene = _scene;
}

const CScene * CSceneMgr::GetCurScene() const
{
	return m_pCurScene;
}

const CScene * CSceneMgr::GetReserveScene() const
{
	return m_pNextScene;
}
