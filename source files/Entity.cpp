#include "PCH.h"
#include "Entity.h"
#include "ImageData.h"
#include "def.h"
#include "Game.h"

CEntity::CEntity(ImageData * _image, float _scale, float _alpha, float _speed, float _angle, float _x, float _y)
	: m_pImage(_image), m_fX(_x), m_fY(_y), m_fSpeed(_speed), m_fScale(_scale), m_fAlpha(_alpha), m_fAngle(_angle), m_bActive(true)
{

}

void CEntity::Draw(Graphics* _graphics)
{
	if (m_pImage)
	{
		float width = m_pImage->image->GetWidth() * m_fScale;
		float height = m_pImage->image->GetHeight() * m_fScale;

		Matrix matrix;
		matrix.RotateAt(m_fAngle, PointF(m_fX, m_fY));
		_graphics->SetTransform(&matrix);

		_graphics->DrawImage(m_pImage->image, (int)m_fX, (int)m_fY, (int)width, (int)height);
		_graphics->ResetTransform();
	}
}

void CEntity::SetImage(ImageData * _image)
{
	m_pImage = _image;
}

ImageData * CEntity::GetImage() const
{
	return m_pImage;
}

void CEntity::SetPos(float _x, float _y)
{
	m_fX = _x;
	m_fY = _y;
}

float CEntity::GetX() const
{
	return m_fX;
}

float CEntity::GetY() const
{
	return m_fY;
}

void CEntity::SetSpeed(float _speed)
{
	m_fSpeed = _speed;
}

float CEntity::GetSpeed() const
{
	return m_fSpeed;
}

void CEntity::SetAngle(float _angle)
{
	m_fAngle = _angle;
}

float CEntity::GetAngle() const
{
	return m_fAngle;
}

void CEntity::SetAlpha(float _alpha)
{
	m_fAlpha = _alpha;
}

float CEntity::GetAlpha() const
{
	return m_fAlpha;
}

void CEntity::SetScale(float _scale)
{
	m_fScale = _scale;
}

float CEntity::GetScale() const
{
	return m_fScale;
}

void CEntity::SetActive(bool _active)
{
	m_bActive = _active;
}

bool CEntity::IsActive() const
{
	return m_bActive;
}
