#pragma once
#include <windows.h>
#define SCENE_TITLE   0
#define SCENE_REVERSI 1
#define SCENE_RESULT 2

#define WM_TITLE   0x0116
#define WM_REVERSI 0x0117

class Game
{
public:
	//�J�n����
	bool Initialize(LPCWSTR windowTitle, int screenwidth, int screenheight);

	//���b�Z�[�W���[�v
	void Run();

private:

	//�E�B���h�E�̍쐬
	bool InitWindow();

	LPCWSTR WindowTitle = L"TitleName";

	int ScreenWidth = 0;

	int ScreenHeight = 0;

	HWND hWnd;
};