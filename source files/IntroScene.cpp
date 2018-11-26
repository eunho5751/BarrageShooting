#include "PCH.h"
#include "IntroScene.h"
#include "StageScene.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "DataMgr.h"
#include "def.h"

CIntroScene::CIntroScene()
	:
	m_pIntroTitle(RESOURCE_MGR().GetImage("intro_title.png")),
	m_pBackground(RESOURCE_MGR().GetImage("intro_background.png")),
	m_pStartButton(RESOURCE_MGR().GetImage("intro_start.png")),
	m_pStartOnButton(RESOURCE_MGR().GetImage("intro_start_on.png")),
	m_pCurButton(m_pStartButton),
	m_bStartButtonClicked(false),
	m_fElapsedTime(.0f),
	m_bCursorInRect(false)
{
	int buttonWidth = m_pCurButton->GetWidth();
	int buttonHeight = m_pCurButton->GetHeight();

	m_StartButtonRect.left = (int)(WINDOW_WIDTH / 2 -  buttonWidth / 2);
	m_StartButtonRect.right = m_StartButtonRect.left + buttonWidth;
	m_StartButtonRect.top = (int)(WINDOW_HEIGHT - buttonHeight * 1.3);
	m_StartButtonRect.bottom = m_StartButtonRect.top + buttonHeight;
}

void CIntroScene::Update(float _time)
{
	//게임시작 버튼을 클릭하지 않았다면
	if (!m_bStartButtonClicked)
	{
		//커서가 게임시작 버튼 영역안에 있음
		if (INPUT_MGR().IsCursorInRect(m_StartButtonRect))
		{
			m_pCurButton = m_pStartOnButton;

			//사운드 추가
			if (!m_bCursorInRect)
			{
				mciSendString(L"play resource/sound/mouseover.wav", NULL, 0, NULL);
				m_bCursorInRect = true;
			}
		}
		else
		{
			//커서가 영역 밖에 있음
			m_pCurButton = m_pStartButton;
		
			m_bCursorInRect = false;
		}

		//게임시작 버튼 클릭
		if (INPUT_MGR().IsMouseClicked(m_StartButtonRect))
		{
			m_bStartButtonClicked = true;
			m_StartButtonClickedPoint = INPUT_MGR().GetCursorPos();
			m_pCurButton = m_pStartButton;

			//사운드 추가
			mciSendString(L"play resource/sound/mouseclick.wav", NULL, 0, NULL);

		}
	}
	//게임시작 버튼을 클릭했다면
	else
	{
		m_fElapsedTime += _time;

		//일정 시간이 넘으면 Scene을 예약함
		if (m_fElapsedTime >= 1.2f)
		{
			//Scene 예약
			//SCENE_MGR().ReserveScene(new CGameScene(DATA_MGR().GetStageData(1)));
			SCENE_MGR().ReserveScene(new CStageScene(DATA_MGR().GetStageData(1)));
		}
	}
}

void CIntroScene::Draw(Graphics* graphics)
{
	graphics->DrawImage(m_pBackground, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	graphics->DrawImage(m_pIntroTitle, WINDOW_WIDTH / 2 - m_pIntroTitle->GetWidth() / 2, 40, 550, 220);
	graphics->DrawImage(m_pCurButton, m_StartButtonRect.left, m_StartButtonRect.top);
}
