#include "PCH.h"
#include "Enemy.h"
#include "EntityMgr.h"

CEnemy::CEnemy(ImageData * _image, float _scale, float _speed, float _x, float _y)
	: CEntity(_image, _scale, 1.0f, _speed, 0.0f, _x, _y)
{

}

void CEnemy::Update(float _time)
{
	
}
