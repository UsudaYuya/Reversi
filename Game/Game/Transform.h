#pragma once

#include "Vector.h"
#include "GameObject.h"

struct Transform :public Component
{
public:
	Vector2 position;
	Vector2 scale;

	//コンストラクタ
	Transform()
	{
		position = Vector2(0, 0);
		scale = Vector2(100, 100);
	}
	Transform(Vector2 _position, Vector2 _scale)
	{
		position = _position;
		scale = _scale;
	}

	~Transform()
	{

	}
};
