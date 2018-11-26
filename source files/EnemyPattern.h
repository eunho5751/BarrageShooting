#pragma once

#include "Enemy.h"
#include "EntityMgr.h"
#include "DataMgr.h"

class CSpiralShooter : public CEnemy
{
private:
	float m_fShotAngle;
	float m_fShotAngleRate;
	float m_fShotSpeed;

public:
	CSpiralShooter(ImageData* _image, float _scale, float _speed, float _x, float _y, float _shotAngle, float _shotAngleRate, float _shotSpeed)
		: CEnemy(_image, _scale, _speed, _x, _y), m_fShotAngle(_shotAngle), m_fShotAngleRate(_shotAngleRate), m_fShotSpeed(_shotSpeed)
	{ }

	virtual void Update(float _time)
	{
		ENTITY_MGR().CreateBullet(this, DATA_MGR().GetImageData("bullet1.bmp"), 1.f, 1.0f, m_fX, m_fY, m_fShotSpeed, m_fShotAngle, 0.0f, 0.0f);
		m_fShotAngle += m_fShotAngleRate;
	}
};

class CSpiralShooter2 : public CEnemy
{
private:
	float m_fShotAngle;
	float m_fShotAngleRate;
	float m_fShotSpeed;

public:
	CSpiralShooter2(ImageData* _image, float _scale, float _speed, float _x, float _y, float _shotAngle, float _shotAngleRate, float _shotSpeed)
		: CEnemy(_image, _scale, _speed, _x, _y), m_fShotAngle(_shotAngle), m_fShotAngleRate(_shotAngleRate), m_fShotSpeed(_shotSpeed)
	{ }

	virtual void Update(float _time)
	{
		ENTITY_MGR().CreateBullet(this, DATA_MGR().GetImageData("bullet2.bmp"), 1.f, 1.0f, m_fX, m_fY, m_fShotSpeed, m_fShotAngle, 1.0f, 0.0f);
		m_fShotAngle += m_fShotAngleRate;
	}
};

class CRandomShooter : public CEnemy
{
private:
	float m_fShotAngle;
	float m_fShotSpeed;

public:
	CRandomShooter(ImageData* _image, float _scale, float _speed, float _x, float _y, float _shotSpeed)
		: CEnemy(_image, _scale, _speed, _x, _y), m_fShotAngle(0.0f), m_fShotSpeed(_shotSpeed)
	{ }

	virtual void Update(float _time)
	{
		ENTITY_MGR().CreateBullet(this, DATA_MGR().GetImageData("bullet3.bmp"), 1.f, 1.0f, m_fX, m_fY, m_fShotSpeed, m_fShotAngle, 0.0f, 0.0f);
		m_fShotAngle += rand() % 100;
	}
};