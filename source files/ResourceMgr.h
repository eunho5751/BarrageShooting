#pragma once

#include "Utility.h"

class CResourceMgr : public Singleton<CResourceMgr>
{
	friend class Singleton<CResourceMgr>;

private:
	map<string, Image*> m_Images;

private:
	CResourceMgr();
	~CResourceMgr();

	void LoadImages(const string& _folderName);
	void UnloadImages();

public:
	Image* GetImage(const string& _imageName);
	void Clear();
};

#define RESOURCE_MGR() CResourceMgr::GetInstance()