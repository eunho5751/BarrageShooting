#pragma once

#include "EntityData.h"

struct CharData : public EntityData
{
	CharData(int _id, ImageData* _image, float _speed, float _scale) 
		: EntityData(_id, _image, _speed, _scale)
	{ }
};