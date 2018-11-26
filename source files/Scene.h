#pragma once

class CScene
{
protected:
	CScene() = default;

public:
	virtual ~CScene() = default;

	virtual void Update(float _time) = 0;
	virtual void Draw(Graphics* graphics) = 0;
};