//=============================================================================
// Program.cpp
// 
//=============================================================================
#include <Windows.h>
#include"Game.h"

// �G���g���[�|�C���g
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,			// �C���X�^���X�ւ̃n���h��
	_In_opt_ HINSTANCE hPrevInstance,	// ���݂ł͖��g�p
	_In_ LPWSTR lpCmdLine,				// �R�}���h���C������
	_In_ int nCmdShow)					// �\�����
{
	Game game;

	game.Initialize(L"BULLETGAME", 800, 700);

	game.Run();

	return 0;
}