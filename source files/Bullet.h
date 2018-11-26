#pragma once

#include "Entity.h"

class CEnemy;

class CBullet : public CEntity
{
protected:
	CEnemy* m_Owner;
	float m_fAngularVelocity;
	float m_fAccel;

public:
	CBullet(CEnemy* m_Owner, ImageData* _image, float _scale, float _alpha, float _speed, float _angle, float _x, float _y, float _angularVelocity, float _accel);

	virtual void Update(float _time);
	virtual void Draw(Graphics* _graphics);

	void SetAngularVelocity(float _angularVelocity);
	float GetAngularVelocity() const;

	void SetAccel(float _accel);
	float GetAccel() const;
};