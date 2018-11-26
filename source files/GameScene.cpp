#include "PCH.h"
#include "GameScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "SceneMgr.h"
#include "EntityMgr.h"
#include "ResourceMgr.h"
#include "DataMgr.h"
#include "StageData.h"
#include "CharData.h"
#include "EnemyData.h"
#include "Player.h"
#include "def.h"

CGameScene::CGameScene(const StageData* _stage)
	: m_pStage(_stage), m_fElapsedTime(.0f), m_bIsGameStatred(false),
	m_pClockImg(RESOURCE_MGR().GetImage("game_clock.png")), 
	m_pGaugeBarShape(RESOURCE_MGR().GetImage("game_bar_shape.png")),
	m_pGaugeBar(RESOURCE_MGR().GetImage("game_bar.png")),
	m_pStageProfile(RESOURCE_MGR().GetImage("game_current_stage.png"))
{
	m_ScrollY = (float)m_pStage->background->GetHeight() - WINDOW_HEIGHT;

	//Entity 할당
	ENTITY_MGR().GetCharPool().Allocate();
	ENTITY_MGR().GetEnemyPool().Allocate();
	ENTITY_MGR().GetBulletPool().Allocate();

	//플레이어 캐릭터를 생성한다.
	ENTITY_MGR().CreateChar(PLAYER().GetCharacter()->id);
	
	//적을 생성한다.
	for (auto& it : m_pStage->enemies)
		ENTITY_MGR().CreateEnemy(get<0>(it)->id, get<1>(it), get<2>(it));

	//ENTITY_MGR().CreateEnemy(1, 250, 250);
}

CGameScene::~CGameScene()
{
	//Entity 삭제
	ENTITY_MGR().GetCharPool().Deallocate();
	ENTITY_MGR().GetEnemyPool().Deallocate();
	ENTITY_MGR().GetBulletPool().Deallocate();
}

void CGameScene::Update(float _time)
{
	if (!m_bIsGameStatred)
	{
		m_fElapsedTime += _time;

		//일정 시간이 지나면 게임을 시작한다.
		if (m_fElapsedTime >= GAME_COUNTDOWN + 1.0f)
		{
			m_bIsGameStatred = true;
			m_fElapsedTime = m_pStage->endureTime;
		}
	}
	else
	{
		//Timer
		if (m_fElapsedTime > 0.0f)
		{
			m_fElapsedTime -= _time;

			//배경 스크롤
			m_ScrollY -= _time * 1.2f * 100.0f;
			if (m_ScrollY + WINDOW_HEIGHT <= 0.0f)
				m_ScrollY += m_pStage->background->GetHeight();

			//Entity Update
			ENTITY_MGR().Update(_time);

			//
			for (auto it : ENTITY_MGR().GetCharPool())
			{
				if (!it->IsActive())
				{
					//게임오버, Scene 예약
					mciSendString(L"play resource/sound/gameover.wav", NULL, 0, NULL);
					SCENE_MGR().ReserveScene(new CGameOverScene(m_pStage));
				}
			}
		}
		else
		{
			//게임 클리어, Scene 예약
			mciSendString(L"play resource/sound/stage_up.wav", NULL, 0, NULL);
			SCENE_MGR().ReserveScene(new CGameClearScene(m_pStage));
			if(PLAYER().GetCurStage() == m_pStage)
				PLAYER().StageUp();
		}
	}
}

void CGameScene::Draw(Graphics * _graphics)
{
	//배경
	if (m_ScrollY < 0.0f)
	{
 		_graphics->DrawImage(m_pStage->background, Rect(0, 0, WINDOW_WIDTH, (int)-m_ScrollY), 0, (int)(m_pStage->background->GetHeight() + m_ScrollY), m_pStage->background->GetWidth(), (int)-m_ScrollY, UnitPixel);
		_graphics->DrawImage(m_pStage->background, Rect(0, (int)-m_ScrollY, WINDOW_WIDTH, (int)(WINDOW_HEIGHT + m_ScrollY)), 0, 0, m_pStage->background->GetWidth(), (int)(WINDOW_HEIGHT + m_ScrollY), UnitPixel);
	}
	else
		_graphics->DrawImage(m_pStage->background, Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), 0, (int)m_ScrollY, m_pStage->background->GetWidth(), WINDOW_HEIGHT, UnitPixel);

	//스테이지
	_graphics->DrawImage(m_pStageProfile, (int)(WINDOW_WIDTH - m_pStageProfile->GetWidth()), (int)(WINDOW_HEIGHT - m_pStageProfile->GetHeight() - 50));
	Font font_(L"맑은 고딕", 20.0f, FontStyleBold, UnitPixel);
	PointF pt_((REAL)(WINDOW_WIDTH - m_pStageProfile->GetWidth() + 10), (REAL)(WINDOW_HEIGHT - 90));
	SolidBrush brush_(Color(0, 0, 0));
	wstring stageNumber = to_wstring(m_pStage->stageNumber);
	stageNumber = L"스테이지 : " + stageNumber;

	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintAntiAlias);
	_graphics->DrawString(stageNumber.c_str(), -1, &font_, pt_, &brush_);
	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintSystemDefault);

	//Entity Draw
	ENTITY_MGR().Draw(_graphics);

	//게이지
	int gaugeWidth = (int)(m_pGaugeBarShape->GetWidth() * 2.5);
	int gaugeHeight = (int)(m_pGaugeBarShape->GetHeight() * 1.5);
	_graphics->DrawImage(m_pClockImg, 0, 0, m_pClockImg->GetWidth() / 2, m_pClockImg->GetHeight() / 2);
	
	if (!m_bIsGameStatred)
	{
		_graphics->DrawImage(m_pGaugeBar, 90, 12, gaugeWidth, gaugeHeight);

		//카운트 다운
		if (m_fElapsedTime < GAME_COUNTDOWN)
		{
			REAL scale = 300.0f;
			wstring& elapsedTime = to_wstring((int)(GAME_COUNTDOWN - floorf(m_fElapsedTime)));
			Font font(L"맑은 고딕", scale -= m_fElapsedTime * 100.0f, FontStyleBold, UnitPixel);
			PointF pt((REAL)(WINDOW_WIDTH / 2 - scale / 1.9), (REAL)(WINDOW_HEIGHT / 2 - scale / 1.5));
			SolidBrush brush(Color(0, 0, 0));
			
			_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintAntiAlias);
			_graphics->DrawString(elapsedTime.c_str(), -1, &font, pt, &brush);
			_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintSystemDefault);
		}
		//카운트다운이 끝났을때, Go 이미지 출력
		else
		{
			Image* go = RESOURCE_MGR().GetImage("game_go.png");
			int width = go->GetWidth();
			int height = go->GetHeight();
			_graphics->DrawImage(go, (int)(WINDOW_WIDTH / 2 - width / 4), (int)(WINDOW_HEIGHT / 2 - height / 3.5), (int)(width / 2), (int)(height / 2));
		}
	}
	else
	{
		_graphics->DrawImage(m_pGaugeBar, 90, 12, (int)((m_fElapsedTime * gaugeWidth) / m_pStage->endureTime), gaugeHeight);
	}

	_graphics->DrawImage(m_pGaugeBarShape, 90, 12, gaugeWidth, gaugeHeight);
	wstring elapsedTime;
	Font font(L"맑은 고딕", 30, FontStyleBold, UnitPixel);
	PointF pt((REAL)(gaugeWidth / 1.7), 15);
	SolidBrush brush(Color(0, 0, 0));
	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintAntiAlias);
	if (m_bIsGameStatred)
		elapsedTime = to_wstring((int)ceilf(m_fElapsedTime));
	else
		elapsedTime = to_wstring((int)ceilf(m_pStage->endureTime));
	_graphics->DrawString(elapsedTime.c_str(), -1, &font, pt, &brush);
	_graphics->SetTextRenderingHint(TextRenderingHint::TextRenderingHintSystemDefault);
}
