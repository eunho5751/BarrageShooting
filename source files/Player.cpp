#include "PCH.h"
#include "Player.h"
#include "StageData.h"
#include "DataMgr.h"
#include "EntityMgr.h"
#include "def.h"

CPlayer::CPlayer()
	: 
	m_pCharData(DATA_MGR().GetCharData(CHAR_DEFAULT_DATA)),
	m_pCurStage(DATA_MGR().GetStageData(1))
{

}

void CPlayer::SetCharacter(const CharData * _data)
{
	m_pCharData = _data;
}

const CharData * CPlayer::GetCharacter() const
{
	return m_pCharData;
}

void CPlayer::StageUp()
{
	const StageData* stage = DATA_MGR().GetStageData(m_pCurStage->stageNumber + 1);
	if (stage != nullptr)
		m_pCurStage = stage;
	else
	{
		//��� �������� Ŭ����, Scene ����
		
	}
}

const StageData * CPlayer::GetCurStage() const
{
	return m_pCurStage;
}
