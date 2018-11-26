#include "PCH.h"
#include "Bullet.h"
#include "EntityMgr.h"
#include "ImageData.h"
#include "def.h"

CBullet::CBullet(CEnemy* _owner, ImageData * _image, float _scale, float _alpha, float _speed, float _angle, float _x, float _y, float _angularVelocity, float _accel)
	: CEntity(_image, _scale, _alpha, _speed, _angle, _x, _y), m_fAngularVelocity(_angularVelocity), m_fAccel(_accel), m_Owner(_owner)
{
	m_fX += m_Owner->GetImage()->image->GetWidth() * m_Owner->GetScale() / 2;
	m_fY += m_Owner->GetImage()->image->GetHeight() * m_Owner->GetScale() / 2;
}

void CBullet::Update(float _time)
{
	float rad = (float)(m_fAngle * M_PI / 180);
	m_fX += 20.0f * m_fSpeed * cos(rad);
	m_fY += 20.0f * m_fSpeed * sin(rad);
	m_fSpeed += m_fAccel;
	m_fAngle += m_fAngularVelocity;

	if (m_fX <= 0.0f || m_fX >= WINDOW_WIDTH || m_fY <= 0.0f || m_fY >= WINDOW_HEIGHT)
		m_bActive = false;
}

//총알은 비트맵으로 처리하기때문에 따로 구현하도록 한다.
//비트맵으로 처리하는 이유는 GDI로 구현했을때의 속도가 GDI+보다 훨씬 빠르다.
void CBullet::Draw(Graphics * _graphics)
{
	if (m_pImage)
	{
		//총알 이미지의 확장자가 bmp가 아니라면 nullptr 반환
		Bitmap* bitmap = dynamic_cast<Bitmap*>(m_pImage->image);
		if (bitmap == nullptr) return;

		UINT width = m_pImage->image->GetWidth();
		UINT height = m_pImage->image->GetHeight();

		//초기화
		HDC hdc = _graphics->GetHDC();
		HDC memDC = CreateCompatibleDC(hdc);
		Graphics* graphics = Graphics::FromHDC(memDC);

		//
		HBITMAP hBitmap;
		bitmap->GetHBITMAP(Color(0, 0, 0, 0), &hBitmap);
		SelectObject(memDC, hBitmap);

		//회전
		Matrix matrix;
		matrix.RotateAt(m_fAngle, PointF(m_fX, m_fY));
		graphics->SetTransform(&matrix);

		//출력
		TransparentBlt(hdc, (int)m_fX, (int)m_fY, (int)(width * m_fScale), (int)(height * m_fScale), memDC, 0, 0, width, height, RGB(255, 255, 255));

		//Release
		delete graphics;
		DeleteObject(hBitmap);
		DeleteDC(memDC);
		_graphics->ReleaseHDC(hdc);
	}
}

void CBullet::SetAngularVelocity(float _angularVelocity)
{
	m_fAngularVelocity = _angularVelocity;
}

void CBullet::SetAccel(float _accel)
{
	m_fAccel = _accel;
}

float CBullet::GetAngularVelocity() const
{
	return m_fAngularVelocity;
}

float CBullet::GetAccel() const
{
	return m_fAccel;
}
