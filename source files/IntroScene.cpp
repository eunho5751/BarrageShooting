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
	//���ӽ��� ��ư�� Ŭ������ �ʾҴٸ�
	if (!m_bStartButtonClicked)
	{
		//Ŀ���� ���ӽ��� ��ư �����ȿ� ����
		if (INPUT_MGR().IsCursorInRect(m_StartButtonRect))
		{
			m_pCurButton = m_pStartOnButton;

			//���� �߰�
			if (!m_bCursorInRect)
			{
				mciSendString(L"play resource/sound/mouseover.wav", NULL, 0, NULL);
				m_bCursorInRect = true;
			}
		}
		else
		{
			//Ŀ���� ���� �ۿ� ����
			m_pCurButton = m_pStartButton;
		
			m_bCursorInRect = false;
		}

		//���ӽ��� ��ư Ŭ��
		if (INPUT_MGR().IsMouseClicked(m_StartButtonRect))
		{
			m_bStartButtonClicked = true;
			m_StartButtonClickedPoint = INPUT_MGR().GetCursorPos();
			m_pCurButton = m_pStartButton;

			//���� �߰�
			mciSendString(L"play resource/sound/mouseclick.wav", NULL, 0, NULL);

		}
	}
	//���ӽ��� ��ư�� Ŭ���ߴٸ�
	else
	{
		m_fElapsedTime += _time;

		//���� �ð��� ������ Scene�� ������
		if (m_fElapsedTime >= 1.2f)
		{
			//Scene ����
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
