#include "PCH.h"
#include "GameClearScene.h"
#include "StageScene.h"
#include "SceneMgr.h"
#include "DataMgr.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "StageData.h"
#include "def.h"

CGameClearScene::CGameClearScene(const StageData* _stage)
	: 
	m_pGameClear(RESOURCE_MGR().GetImage("game_clear.jpg")),
	m_pStage(_stage)
{ }

void CGameClearScene::Update(float _time)
{
	if (INPUT_MGR().IsKeyPushed(VK_SPACE))
	{
		//Scene 예약(스테이지 선택)
		const StageData* stage = DATA_MGR().GetStageData(m_pStage->stageNumber + 1);
		SCENE_MGR().ReserveScene(new CStageScene(stage != nullptr ? stage : m_pStage));
	}
}

void CGameClearScene::Draw(Graphics * _graphics)
{
	_graphics->DrawImage(m_pGameClear, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	Font font(L"맑은 고딕", 30.0f, FontStyleBold, UnitPixel);
	PointF pt((REAL)(WINDOW_WIDTH / 5 - 30), (REAL)(WINDOW_HEIGHT - 100));
	SolidBrush brush(Color(255, 90, 0));

	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintAntiAlias);
	_graphics->DrawString(L"PRESS [SPACE BAR] TO CONTINUE", -1, &font, pt, &brush);
	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintSystemDefault);
}
