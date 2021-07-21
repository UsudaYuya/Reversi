#pragma once
#include<Windows.h>
#include"Vector2.h"

class Behaviour
{
public:
	Behaviour() {};
	virtual ~Behaviour() {};

	virtual void Start(HWND) {  }
	virtual void Start(HWND,int) {  }
	virtual void Update(HWND) {  }
	virtual void OnMouse(HWND,Vector2) {  }

	virtual void Draw(HWND) {  }

	bool enabled = true;
};
