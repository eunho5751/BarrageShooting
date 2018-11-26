#pragma once

struct ImageData;

struct EntityData
{
	int id;
	ImageData* imageData;
	float speed;
	float scale;

	EntityData(int _id, ImageData* _image, float _speed, float _scale)
		: id(_id), imageData(_image), speed(_speed), scale(_scale) 
	{ }
};