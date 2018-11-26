#include "PCH.h"
#include "StageScene.h"
#include "GameScene.h"
#include "EnemyData.h"
#include "StageData.h"
#include "ImageData.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "DataMgr.h"
#include "InputMgr.h"
#include "Player.h"
#include "def.h"

CStageScene::CStageScene(const StageData * _scene)
	: m_pCurStage(_scene),
	m_EnemyIDCounter(0),
	m_pBackground(RESOURCE_MGR().GetImage("stage_select_background.png")),
	m_pSelectImg(RESOURCE_MGR().GetImage("stage_select.png")),
	m_pCantEnter(RESOURCE_MGR().GetImage("stage_select_cant_enter.png"))
{ }

void CStageScene::Update(float _time)
{
	//�������� ���� ȭ��
	const StageData* stage = nullptr;
	if (INPUT_MGR().IsKeyPushed(VK_LEFT, 0x0001))
		stage = DATA_MGR().GetStageData(m_pCurStage->stageNumber - 1);
	else if (INPUT_MGR().IsKeyPushed(VK_RIGHT, 0x0001))
		stage = DATA_MGR().GetStageData(m_pCurStage->stageNumber + 1);
	else if (INPUT_MGR().IsKeyPushed(VK_UP, 0x0001))
	{
		if (m_pCurStage->enemies.size() > (size_t)m_EnemyIDCounter + 1)
		{
			mciSendString(L"play resource/sound/swapEnemy.wav", NULL, 0, NULL);
			m_EnemyIDCounter++;
		}
	}
	else if (INPUT_MGR().IsKeyPushed(VK_DOWN, 0x0001))
	{
		if (0 < m_EnemyIDCounter)
		{
			mciSendString(L"play resource/sound/swapEnemy.wav", NULL, 0, NULL);
			m_EnemyIDCounter--;
		}
	}
	//�������� ���� Ȯ��
	else if (INPUT_MGR().IsKeyPushed(VK_SPACE, 0x0001))
	{
		//�ڰ��� ����Ұ��
		if (PLAYER().GetCurStage()->stageNumber >= m_pCurStage->stageNumber)
		{
			mciSendString(L"play resource/sound/stage_selected.wav", NULL, 0, NULL);
			SCENE_MGR().ReserveScene(new CGameScene(m_pCurStage));
		}
		else
			mciSendString(L"play resource/sound/cant_enter.wav", NULL, 0, NULL);
	}

	if (stage != nullptr)
	{
		mciSendString(L"play resource/sound/swapStage.wav", NULL, 0, NULL);
		m_pCurStage = stage;
		m_EnemyIDCounter = 0;
	}
}

void CStageScene::Draw(Graphics * _graphics)
{
	Image* enemy = get<0>(m_pCurStage->enemies[m_EnemyIDCounter])->imageData->image;
	_graphics->DrawImage(m_pBackground, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	_graphics->DrawImage(m_pSelectImg, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (PLAYER().GetCurStage()->stageNumber < m_pCurStage->stageNumber)
		_graphics->DrawImage(m_pCantEnter, 160, 150, 495, 325);
	_graphics->DrawImage(enemy, (int)(402 - enemy->GetWidth() / 2), (int)(348 - enemy->GetHeight()));

	Font topFont(L"���� ���", 50.0f, FontStyleBold, UnitPixel);
	PointF topPt((REAL)(WINDOW_WIDTH / 2 - 225), (REAL)50);
	Font stageFont(L"���� ���", 20.0f, FontStyleBold, UnitPixel);
	PointF stagePt((REAL)(WINDOW_WIDTH / 2 - 50), (REAL)170);
	PointF timePt((REAL)(WINDOW_WIDTH / 2 - 77), (REAL)440);
	SolidBrush brush(Color(0, 0, 0));

	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintAntiAlias);

	_graphics->DrawString(L"�������� ���� ȭ��", -1, &topFont, topPt, &brush);

	wstring stage;

	stage = L"�������� : " + to_wstring(m_pCurStage->stageNumber);
	_graphics->DrawString(stage.c_str(), -1, &stageFont, stagePt, &brush);

	stage = L"��Ƽ�� �ð� : " + to_wstring((int)m_pCurStage->endureTime);
	_graphics->DrawString(stage.c_str(), -1, &stageFont, timePt, &brush);

	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintSystemDefault);
}
