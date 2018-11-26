#pragma once

struct ImageData;

class CEntity
{
protected:
	ImageData* m_pImage;
	float m_fX, m_fY;
	float m_fSpeed;
	float m_fAlpha;
	float m_fAngle;
	float m_fScale;
	bool m_bActive;

protected:
	CEntity(ImageData* _image, float _scale, float _alpha, float _speed, float _angle, float _x, float _y);

public:
	virtual ~CEntity() = default;

	virtual void Update(float _time) = 0;
	virtual void Draw(Graphics* _graphics);

	void SetImage(ImageData* _image);
	ImageData* GetImage() const;

	void SetPos(float _x, float _y);
	float GetX() const;
	float GetY() const;

	void SetSpeed(float _speed);
	float GetSpeed() const;

	void SetAngle(float _angle);
	float GetAngle() const;

	void SetAlpha(float _alpha);
	float GetAlpha() const;

	void SetScale(float _scale);
	float GetScale() const;

	void SetActive(bool _active);
	bool IsActive() const;
};