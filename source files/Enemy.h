#pragma once

#include "Entity.h"

class CEnemy : public CEntity
{
protected:
	CEnemy(ImageData* _image, float _scale, float _speed, float _x, float _y);

public:
	virtual void Update(float _time);
};