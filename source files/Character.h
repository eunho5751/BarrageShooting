#pragma once

#include "Entity.h"

class CCharacter : public CEntity
{
public:
	CCharacter(ImageData* _image, float _scale, float _speed, float _x, float _y);

	virtual void Update(float _time);
};