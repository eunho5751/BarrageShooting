#include "PCH.h"
#include "GameOverScene.h"
#include "StageScene.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "def.h"

CGameOverScene::CGameOverScene(const StageData* _stage)
	: 
	m_pGameOver(RESOURCE_MGR().GetImage("game_over.png")),
	m_pStage(_stage)
{ }

void CGameOverScene::Update(float _time)
{
	if (INPUT_MGR().IsKeyPushed(VK_SPACE, 0x0001))
	{
		//Scene 예약(스테이지 선택)
		SCENE_MGR().ReserveScene(new CStageScene(m_pStage));
	}
}

void CGameOverScene::Draw(Graphics * _graphics)
{
	_graphics->DrawImage(m_pGameOver, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	Font font(L"맑은 고딕", 30.0f, FontStyleBold, UnitPixel);
	PointF pt((REAL)(WINDOW_WIDTH / 5 - 30), (REAL)(WINDOW_HEIGHT - 100));
	SolidBrush brush(Color(255, 90, 0));

	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintAntiAlias);
	_graphics->DrawString(L"PRESS [SPACE BAR] TO CONTINUE", -1, &font, pt, &brush);
	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintSystemDefault);
}
