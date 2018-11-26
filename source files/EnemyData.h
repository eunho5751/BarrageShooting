#pragma once

#include "EntityData.h"

struct EnemyData : public EntityData
{
	string patternName;

	EnemyData(int _id, const string& _patternName, ImageData* _image, float _speed, float _scale)
		: EntityData(_id, _image, _speed, _scale), patternName(_patternName)
	{ }
};