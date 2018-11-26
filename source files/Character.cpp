#include "PCH.h"
#include "Character.h"
#include "EntityMgr.h"
#include "InputMgr.h"
#include "ImageData.h"
#include "def.h"

CCharacter::CCharacter(ImageData * _image, float _scale, float _speed, float _x, float _y)
	: CEntity(_image, _scale, 1.0f, _speed, 0.0f, _x, _y)
{

}

void CCharacter::Update(float _time)
{
	//캐릭터 이동
	float distance = m_fSpeed * _time * 300.0f;
	float vx = (float)(INPUT_MGR().IsKeyPushed(VK_LEFT) ? -1 : (INPUT_MGR().IsKeyPushed(VK_RIGHT) ? 1: 0));
	float vy = (float)(INPUT_MGR().IsKeyPushed(VK_UP) ? -1 : (INPUT_MGR().IsKeyPushed(VK_DOWN) ? 1 : 0));
	float dst_x = m_fX + vx * distance;
	float dst_y = m_fY + vy * distance;
	float dx = dst_x - m_fX;
	float dy = dst_y - m_fY;
	float d = sqrtf(dx*dx + dy*dy);

	if (d > distance)
	{
		dx *= distance / d;
		dy *= distance / d;
	}

	dst_x = m_fX + dx;
	dst_y = m_fY + dy;

	if (dst_x < 0 || dst_x + m_pImage->image->GetWidth() * m_fScale + 5 > WINDOW_WIDTH || dst_y + m_pImage->image->GetHeight() * m_fScale + 25 > WINDOW_HEIGHT || dst_y < 0)
		return;

	m_fX += dx;
	m_fY += dy;
}
