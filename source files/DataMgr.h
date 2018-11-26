#pragma once

#include "PCH.h"
#include "Utility.h"

struct CharData;
struct EnemyData;
struct ImageData;
struct StageData;

class CDataMgr : public Singleton<CDataMgr>
{
	friend class Singleton<CDataMgr>;
	
private:
	map<int, CharData*> m_CharDataMap;
	map<int, EnemyData*> m_EnemyDataMap;
	map<string, ImageData*> m_ImageDataMap;
	map<int, StageData*> m_StageDataMap;

private:
	CDataMgr();
	~CDataMgr() = default;

	void LoadCharData();
	void LoadEnemyData();
	void LoadImageData();
	void LoadStageData();

public:
	const CharData* GetCharData(int _id) const;
	const EnemyData* GetEnemyData(int _id) const;
	ImageData* GetImageData(const string& _imageName) const;
	const StageData* GetStageData(int _stageNumber) const;
};

#define DATA_MGR() CDataMgr::GetInstance()