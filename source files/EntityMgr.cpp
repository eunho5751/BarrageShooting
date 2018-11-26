#include "PCH.h"
#include "EntityMgr.h"
#include "DataMgr.h"
#include "CharData.h"
#include "ImageData.h"
#include "EnemyData.h"
#include "EnemyPattern.h"
#include "def.h"

CEntityMgr::CEntityMgr()
	: m_CharPool(CHAR_POOL_SIZE, CHAR_POOL_COUNT), m_EnemyPool(ENEMY_POOL_SIZE, ENEMY_POOL_COUNT), m_BulletPool(BULLET_POOL_SIZE, BULLET_POOL_COUNT)
{

}

void CEntityMgr::Update(float _time)
{
	//Entities Update
	for (auto it = m_CharPool.begin(); it != m_CharPool.end();)
	{
		(*it)->Update(_time);
		if (!(*it)->IsActive())
			m_CharPool.Delete(*it++);
		else
			++it;
	}

	for (auto it = m_EnemyPool.begin(); it != m_EnemyPool.end();)
	{
		(*it)->Update(_time);
		if (!(*it)->IsActive())
			m_EnemyPool.Delete(*it++);
		else
			++it;
	}

	for (auto it = m_BulletPool.begin(); it != m_BulletPool.end();)
	{
		(*it)->Update(_time);
		if (!(*it)->IsActive())
			m_BulletPool.Delete(*it++);
		else
			++it;
	}

	//충돌 체크
	for (auto character : m_CharPool)
	{
		UINT myWidth = (UINT)(character->GetImage()->image->GetWidth() * character->GetScale());
		UINT myHeight = (UINT)(character->GetImage()->image->GetHeight() * character->GetScale());

		//총알과 충돌체크
		for (auto bullet : m_BulletPool)
		{
			UINT yourWidth = (UINT)(bullet->GetImage()->image->GetWidth() * bullet->GetScale());
			UINT yourHeight = (UINT)(bullet->GetImage()->image->GetHeight() * bullet->GetScale());

			float dx = (character->GetX() + myWidth / 2) - (bullet->GetX() + yourWidth / 2);
			float dy = (character->GetY() + myHeight / 2) - (bullet->GetY() + yourHeight / 2);
			float r = dx * dx + dy * dy;

			float range = character->GetImage()->hitRadius * (myWidth < myHeight ? myWidth / 2 : myHeight / 2) * character->GetScale()
				+ bullet->GetImage()->hitRadius * (yourWidth < yourHeight ? yourWidth / 2 : yourHeight / 2) * bullet->GetScale();
			if (range * range >= r)
				character->SetActive(false);
		}

		//캐릭터가 활성화상태인지 확인(비활성화 상태면 어차피 삭제됨)
		if (character->IsActive())
		{
			//적과 충돌체크
			for (auto enemy : m_EnemyPool)
			{
				UINT yourWidth = (UINT)(enemy->GetImage()->image->GetWidth() * enemy->GetScale());
				UINT yourHeight = (UINT)(enemy->GetImage()->image->GetHeight() * enemy->GetScale());

				float dx = (character->GetX() + myWidth / 2) - (enemy->GetX() + yourWidth / 2);
				float dy = (character->GetY() + myHeight / 2) - (enemy->GetY() + yourHeight / 2);
				float r = dx * dx + dy * dy;

				float range = character->GetImage()->hitRadius * (myWidth < myHeight ? myWidth / 2 : myHeight / 2) * character->GetScale()
					+ enemy->GetImage()->hitRadius * (yourWidth < yourHeight ? yourWidth / 2 : yourHeight / 2) * enemy->GetScale();
				if (range * range >= r)
					character->SetActive(false);
			}
		}
	}
}

void CEntityMgr::Draw(Graphics * _graphics)
{
	//Entities Draw
	for (auto it : m_CharPool)
		it->Draw(_graphics);
	for (auto it : m_EnemyPool)
		it->Draw(_graphics);
	for (auto it : m_BulletPool)
		it->Draw(_graphics);
}

void CEntityMgr::CreateChar(int _id)
{
	const CharData* data = DATA_MGR().GetCharData(_id);
	new(m_CharPool.New()) CCharacter(data->imageData, data->scale, data->speed, WINDOW_WIDTH / 2 - data->imageData->image->GetWidth() * data->scale / 2, WINDOW_HEIGHT - data->imageData->image->GetHeight() * data->scale - 100);
}

void CEntityMgr::CreateEnemy(int _id, float _x, float _y)
{
	const EnemyData* data = DATA_MGR().GetEnemyData(_id);

	if (data->patternName == "SpiralShooter")
	{
		new(m_EnemyPool.New()) CSpiralShooter(data->imageData, data->scale, data->speed, _x, _y, 0.0f, 10.0f, 0.1f);
	}
	else if (data->patternName == "SpiralShooter2")
	{
		new(m_EnemyPool.New()) CSpiralShooter2(data->imageData, data->scale, data->speed, _x, _y, 0.0f, 15.0f, 0.23f);
	}
	else if (data->patternName == "RandomShooter")
	{
		new(m_EnemyPool.New()) CRandomShooter(data->imageData, data->scale, data->speed, _x, _y, 0.1f);
	}
}

void CEntityMgr::CreateBullet(CEnemy* _owner, ImageData * _image, float _scale, float _alpha, float _x, float _y, float _speed, float _angle, float _angularVelocity, float _accel)
{
	new(m_BulletPool.New()) CBullet(_owner, _image, _scale, _alpha, _speed, _angle, _x, _y, _angularVelocity, _accel);
}

CEntityPool<CCharacter>& CEntityMgr::GetCharPool()
{
	return m_CharPool;
}

CEntityPool<CEnemy>& CEntityMgr::GetEnemyPool()
{
	return m_EnemyPool;
}

CEntityPool<CBullet>& CEntityMgr::GetBulletPool()
{
	return m_BulletPool;
}
