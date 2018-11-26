#include "PCH.h"
#include "ResourceMgr.h"
#include "Game.h"
#include "def.h"

CResourceMgr::CResourceMgr()
{
	LoadImages(CHAR_RESOURCE_FOLDER);
	LoadImages(ENEMY_RESOURCE_FOLDER);
	LoadImages(BULLET_RESOURCE_FOLDER);
	LoadImages(BACKGROUND_RESOURCE_FOLDER);
	LoadImages(ETC_RESOURCE_FOLDER);
}

CResourceMgr::~CResourceMgr()
{

}

void CResourceMgr::LoadImages(const string& _folderName)
{
	//�������� �̹����� �о� map�� �����Ѵ�.
	_finddata_t fd;
	string path = _folderName + "/*.*";
	intptr_t handle = _findfirst(path.c_str(), &fd);
	if (handle != -1)
	{
		do
		{
			if (!strcmp(fd.name, ".") || !strcmp(fd.name, "..")) continue;

			Image* image;
			WCHAR fileName[32], filePath[128];
			int length1 = MultiByteToWideChar(CP_ACP, 0, fd.name, strlen(fd.name), fileName, sizeof(fileName));
			int length2 = MultiByteToWideChar(CP_ACP, 0, _folderName.c_str(), strlen(_folderName.c_str()), filePath, sizeof(filePath));
			fileName[length1] = '\0';
			filePath[length2] = '\0';
			wstring file = filePath, name = fileName;
			file += '/';
			file += name;

			//Ȯ���� Ȯ��
			if (name.substr(name.find('.') + 1, name.length()) != L"bmp")
				image = Image::FromFile(file.c_str());
			else
				image = Bitmap::FromFile(file.c_str());
			if (image->GetLastStatus() == Ok)
				m_Images.emplace(fd.name, image);
			else
				GAME::Destroy(fileName, TEXT("�̹��� �ε� ����"), MB_OK | MB_ICONERROR);
		} while (_findnext(handle, &fd) == 0);
	}
}

void CResourceMgr::UnloadImages()
{
	for (auto it : m_Images)
		delete it.second;
}

Image* CResourceMgr::GetImage(const string& _imageName)
{
	//���� ó�� �ؾ���
	auto it = m_Images.find(_imageName);
	if (it != m_Images.end())
		return m_Images.at(_imageName); 
	else
	{
		GAME::Destroy(TEXT("GetImage �Լ�"), TEXT("���������ʴ� �̹����� �����Ͽ����ϴ�.\n���α׷��� �����մϴ�."), MB_OK | MB_ICONERROR);
		return nullptr;
	}
}

void CResourceMgr::Clear()
{
	UnloadImages();
}
