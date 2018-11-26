#pragma once

struct ImageData
{
	Image* image;
	int frameWidth, frameHeight;
	float hitRadius;

	ImageData(Image* _image, int _frameWidth, int _frameHeight, float _hitRadius)
		: image(_image), hitRadius(_hitRadius), frameWidth(_frameWidth), frameHeight(_frameHeight)
	{ }
};