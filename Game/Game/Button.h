#pragma once
#include<Windows.h>
#include"Vector2.h"
#include"Draw.h"

class Button
{
	Vector2 leftUp;		//¶ã
	Vector2 rightDown;	//‰E‰º
	COLORREF color;
public:
	Button() : leftUp(0), rightDown(0) { color = RGB(0, 0, 0); }
	Button(Vector2 _leftUp, Vector2 _rightDown)
	{
		leftUp = _leftUp;
		rightDown = _rightDown;
		color = RGB(0, 0, 0);
	}
	Button(Vector2 _leftUp, Vector2 _rightDown, COLORREF _color)
	{
		leftUp = _leftUp;
		rightDown = _rightDown;
		color = _color;
	}

	//ÚG
	bool Contact(Vector2 pos)
	{
		if (pos.x > leftUp.x&& pos.y > leftUp.y)
			if (pos.x < rightDown.x && pos.y < rightDown.y)
				return true;
		return false;
	}

	//•`ŽÊ
	void Draw(HDC hdc)
	{
		Draw::Square(hdc, leftUp - Vector2(2, 2), rightDown + Vector2(2, 2), RGB(153, 153, 153));
		Draw::Square(hdc, leftUp, rightDown, color);
	}

	void Draw(HDC hdc, LPCWSTR text,int scale,COLORREF t_color)
	{
		Draw::Square(hdc, leftUp - Vector2(2, 2), rightDown + Vector2(2, 2), RGB(153, 153, 153));
		Draw::Square(hdc, leftUp, rightDown, color);
		Draw::Text(hdc, leftUp + ((rightDown - leftUp) / 2),scale,text, t_color,color);
	}
};
