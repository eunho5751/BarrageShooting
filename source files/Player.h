#pragma once

#include "Utility.h"

struct CharData;
struct StageData;

class CPlayer : public Singleton<CPlayer>
{
	friend class Singleton<CPlayer>;

private:
	const CharData* m_pCharData;
	const StageData* m_pCurStage;

private:
	CPlayer();
	~CPlayer() = default;

public:
	void SetCharacter(const CharData* _data);
	const CharData* GetCharacter() const;

	void StageUp();
	const StageData* GetCurStage() const;
};

#define PLAYER() CPlayer::GetInstance()