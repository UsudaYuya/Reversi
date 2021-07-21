//=============================================================================
// Program.cpp
// 
//=============================================================================
#include <Windows.h>
#include"Game.h"

// エントリーポイント
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,			// インスタンスへのハンドル
	_In_opt_ HINSTANCE hPrevInstance,	// 現在では未使用
	_In_ LPWSTR lpCmdLine,				// コマンドライン引数
	_In_ int nCmdShow)					// 表示状態
{
	Game game;

	game.Initialize(L"BULLETGAME", 800, 700);

	game.Run();

	return 0;
}