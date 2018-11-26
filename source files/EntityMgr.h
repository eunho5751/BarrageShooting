#pragma once

#include "Utility.h"
#include "EntityPool.h"

//템플릿때문에 포함시켜야함
#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"

class CEntityMgr : public Singleton<CEntityMgr>
{
	friend class Singleton<CEntityMgr>;

private:
	CEntityPool<CCharacter> m_CharPool;
	CEntityPool<CEnemy> m_EnemyPool;
	CEntityPool<CBullet> m_BulletPool;

private:
	CEntityMgr();
	~CEntityMgr() = default;

public:
	void Update(float _time);
	void Draw(Graphics* _graphics);

	void CreateChar(int _id);
	void CreateEnemy(int _id, float _x, float _y);
	void CreateBullet(CEnemy* _owner, ImageData* _image, float _scale, float _alpha, float _x, float _y, float _speed, float _angle, float _angularVelocity, float _accel);

	CEntityPool<CCharacter>& GetCharPool();
	CEntityPool<CEnemy>& GetEnemyPool();
	CEntityPool<CBullet>& GetBulletPool();
};

#define ENTITY_MGR() CEntityMgr::GetInstance()