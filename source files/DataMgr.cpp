#include "PCH.h"
#include "DataMgr.h"
#include "CharData.h"
#include "EnemyData.h"
#include "StageData.h"
#include "ImageData.h"
#include "ResourceMgr.h"
#include "Game.h"
#include "def.h"

CDataMgr::CDataMgr()
{
	LoadImageData();
	LoadCharData();
	LoadEnemyData();
	LoadStageData();
}

void CDataMgr::LoadCharData()
{
	//ĳ���� ������ �ε�
	fstream stream(CHAR_DATA_PATH);

	if (stream.fail())
	{
		GAME::Destroy(TEXT("�־���ϴµ�..?"), TEXT("ĳ���� ������ ������ �����!"), MB_OK | MB_ICONERROR);
		return;
	}

	string line;

	while (true)
	{
		std::getline(stream, line);
		if (line == "[")
		{
			int id = -1;
			float speed = .0f;
			float scale = .0f;
			ImageData* image = nullptr;

			do
			{
				std::getline(stream, line);
				if (line == "<id>")
				{
					std::getline(stream, line);
					id = atoi(line.c_str());
				}
				else if (line == "<speed>")
				{
					std::getline(stream, line);
					speed = (float)atof(line.c_str());
				}
				else if (line == "<scale>")
				{
					std::getline(stream, line);
					scale = (float)atof(line.c_str());
				}
				else if (line == "<image>")
				{
					std::getline(stream, line);
					image = m_ImageDataMap.at(line);//
				}
			} while (line != "]");

			//������ ����
			if (id == -1 || image == nullptr)
			{
				GAME::Destroy(TEXT("ĳ���� ������ �ε� ����"), TEXT("ĳ���� �����Ϳ� ������ �ֽ��ϴ�.\n�߸� �Էµ� ���� ������ Ȯ���غ�����."), MB_OK | MB_ICONERROR);
				return;
			}

			m_CharDataMap.emplace(make_pair(id, new CharData(id, image, speed, scale)));
		}
		else if (stream.eof())
			break;
	}
}

void CDataMgr::LoadEnemyData()
{
	//�� ������ �ε�
	fstream stream(ENEMY_DATA_PATH);

	if (stream.fail())
	{
		GAME::Destroy(TEXT("�־���ϴµ�..?"), TEXT("�� ������ ������ �����!"), MB_OK | MB_ICONERROR);
		return;
	}

	string line;

	while (true)
	{
		std::getline(stream, line);
		if (line == "[")
		{
			int id = -1;
			string patternName = "";
			float speed = -1.f;
			float scale = -1.f;
			ImageData* image = nullptr;

			do
			{
				std::getline(stream, line);
				if (line == "<id>")
				{
					std::getline(stream, line);
					id = atoi(line.c_str());
				}
				else if (line == "<speed>")
				{
					std::getline(stream, line);
					speed = (float)atof(line.c_str());
				}
				else if (line == "<scale>")
				{
					std::getline(stream, line);
					scale = (float)atof(line.c_str());
				}
				else if (line == "<image>")
				{
					std::getline(stream, line);
					image = m_ImageDataMap.at(line);//
				}
				else if (line == "<pattern>")
				{
					std::getline(stream, line);
					patternName = line;
				}
			} while (line != "]");

			//������ ����
			if (id == -1 || image == nullptr || patternName == "" || speed == -1.f || scale == -1.f)
			{
				GAME::Destroy(TEXT("�� ������ �ε� ����"), TEXT("�� �����Ϳ� ������ �ֽ��ϴ�.\n[[ <id>, <image>, <scale>, <speed>, <pattern> ]]\n��(��) ��� �ԷµǾ����� Ȯ���ϼ���."), MB_OK | MB_ICONERROR);
				return;
			}

			m_EnemyDataMap.emplace(make_pair(id, new EnemyData(id, patternName, image, speed, scale)));
		}
		else if (stream.eof())
			break;
	}
}

void CDataMgr::LoadImageData()
{
	//�̹��� ������ �ε�
	fstream stream(IMAGE_DATA_PATH);

	if (stream.fail())
	{
		GAME::Destroy(TEXT("�־���ϴµ�..?"), TEXT("�̹��� ������ ������ �����!"), MB_OK | MB_ICONERROR);
		return;
	}

	string line;

	while (true)
	{
		std::getline(stream, line);
		if (line == "[")
		{
			string imageName;
			Image* image = nullptr;
			float hitRadius = -1.f;
			int frameWidth = -1, frameHeight = -1;

			do
			{
				std::getline(stream, line);
				if (line == "<image>")
				{
					std::getline(stream, line);
					image = RESOURCE_MGR().GetImage(line);
					imageName = line;
				}
				else if (line == "<hitRadius>")
				{
					std::getline(stream, line);
					hitRadius = (float)atof(line.c_str());
				}
				else if (line == "<frameLength>")
				{
					std::getline(stream, line);
					int at = line.find(',');
					frameWidth = atoi(line.substr(0, at).c_str());
					frameHeight = atoi(line.substr(at + 1, line.length()).c_str());
				}
			} while (line != "]");

			//������ ����
			if (image == nullptr || hitRadius == -1.f || frameWidth == -1 || frameHeight == -1)
			{
				GAME::Destroy(TEXT("�̹��� ������ �ε� ����"), TEXT("�̹��� �����Ϳ� ������ �ֽ��ϴ�.\n[[ <image>, <hitRadius>, <frameLength> ]]\n��(��) ��� �ԷµǾ����� Ȯ���ϼ���."), MB_OK | MB_ICONERROR);
				return;
			}

			m_ImageDataMap.emplace(make_pair(imageName, new ImageData(image, frameWidth, frameHeight, hitRadius)));
		}
		else if (stream.eof())
			break;
	}
}

void CDataMgr::LoadStageData()
{
	//�������� ������ �ε�
	fstream stream(STAGE_DATA_PATH);

	if (stream.fail())
	{
		GAME::Destroy(TEXT("�־���ϴµ�..?"), TEXT("�������� ������ ������ �����!"), MB_OK | MB_ICONERROR);
		return;
	}

	string line;

	while (true)
	{
		std::getline(stream, line);
		if (line == "[")
		{
			int stageNumber = -1;
			float endureTime = -1.f;
			Image* background = nullptr;
			vector<StageData::enemy_tuple_type> enemies;

			do
			{
				std::getline(stream, line);
				if (line == "<stageNumber>")
				{
					std::getline(stream, line);
					stageNumber = atoi(line.c_str());
				}
				else if (line == "<endureTime>")
				{
					std::getline(stream, line);
					endureTime = (float)atof(line.c_str());
				}
				else if (line == "<background>")
				{
					std::getline(stream, line);
					background = RESOURCE_MGR().GetImage(line.c_str());
				}
				else if (line == "<enemy>")
				{
					while (true)
					{
						std::getline(stream, line);
						if (line[0] == ']' || line[0] == '<') break;

						int at1 = line.find(','), at2;

						const EnemyData* enemy = nullptr;
						int enemyId = atoi(line.substr(0, at1++).c_str());
						float enemyX = (float)atof(line.substr(at1, at2 = line.find(',', at1)).c_str());
						float enemyY = (float)atof(line.substr(at2 + 1, line.length()).c_str());

						//���� ��������������� ����ó�� �ؾ���
						enemy = m_EnemyDataMap.at(enemyId);

						enemies.emplace_back(make_tuple(enemy, enemyX, enemyY));
					}
				}
			} while (line != "]");

			//������ ����
			if (stageNumber == -1 || endureTime == -1.f || background == nullptr || enemies.empty())
			{
				GAME::Destroy(TEXT("�������� ������ �ε� ����"), TEXT("�������� �����Ϳ� ������ �ֽ��ϴ�.\n[[ <stageNumber>, <endureTime>, <background>, <enemy> ]]\n��(��) ��� �ԷµǾ�����  Ȯ���ϼ���."), MB_OK | MB_ICONERROR);
				return;
			}

			m_StageDataMap.emplace(make_pair(stageNumber, new StageData(stageNumber, endureTime, background, enemies)));
		}
		else if (stream.eof())
			break;
	}
}

const CharData* CDataMgr::GetCharData(int _id) const
{
	//���� ó�� �ؾ���
	auto it = m_CharDataMap.find(_id);
	if(it != m_CharDataMap.end())
		return m_CharDataMap.at(_id);
	else
	{
		GAME::Destroy(TEXT("GetCharData �Լ�"), TEXT("���������ʴ� ĳ���� �����͸� �����Ͽ����ϴ�.\n���α׷��� �����մϴ�."), MB_OK | MB_ICONERROR);
		return nullptr;
	}
}

const EnemyData* CDataMgr::GetEnemyData(int _id) const
{
	//���� ó�� �ؾ���
	auto it = m_EnemyDataMap.find(_id);
	if (it != m_EnemyDataMap.end())
		return m_EnemyDataMap.at(_id);
	else
	{
		GAME::Destroy(TEXT("GetEnemyData �Լ�"), TEXT("���������ʴ� �� �����͸� �����Ͽ����ϴ�.\n���α׷��� �����մϴ�."), MB_OK | MB_ICONERROR);
		return nullptr;
	}
}

const StageData* CDataMgr::GetStageData(int _stageNumber) const
{
	//���� ó�� �ؾ���
	auto it = m_StageDataMap.find(_stageNumber);
	if (it != m_StageDataMap.end())
		return m_StageDataMap.at(_stageNumber);
	else
		return nullptr; // ��� �������� Ŭ����
}

ImageData* CDataMgr::GetImageData(const string & _imageName) const
{
	//���� ó�� �ؾ���
	auto it = m_ImageDataMap.find(_imageName);
	if(it != m_ImageDataMap.end())
		return m_ImageDataMap.at(_imageName);
	else
	{
		GAME::Destroy(TEXT("GetImageData �Լ�"), TEXT("���������ʴ� �̹��� �����͸� �����Ͽ����ϴ�.\n���α׷��� �����մϴ�."), MB_OK | MB_ICONERROR);
		return nullptr;
	}
}
