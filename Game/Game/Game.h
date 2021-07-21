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
	//開始処理
	bool Initialize(LPCWSTR windowTitle, int screenwidth, int screenheight);

	//メッセージループ
	void Run();

private:

	//ウィンドウの作成
	bool InitWindow();

	LPCWSTR WindowTitle = L"TitleName";

	int ScreenWidth = 0;

	int ScreenHeight = 0;

	HWND hWnd;
};