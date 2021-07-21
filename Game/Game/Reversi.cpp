#include"Reversi.h"

void Reversi::Start(HWND hwnd,int _level)
{
	level = _level;
	if (level == 1)
		OutputDebugString(L"\n 1 \n");
	else if (level == 2)
		OutputDebugString(L"\n 2 \n");
	else if (level == 3)
		OutputDebugString(L"\n 3 \n");
	state = STATE::PLAYER;
	Reset();//�΂̃��Z�b�g�ƃ{�^���̐ݒ�
	Draw(hwnd);
}

void Reversi::Update(HWND hwnd)
{
	if (state == STATE::NPC)//
	{
		Sleep(1000);//�ҋ@
		if (Npc(hwnd, BLACK, level))
		{
			//�I���`�F�b�N
			if (Win() != 0)
				state = STATE::RESULT;//���U���g�̊J�n
			else {
				if (Board_PutCount(WHITE) != 0)
					state = STATE::PLAYER;//�^�[���̕ύX
			}
			Draw(hwnd);
		}
	}
}

void Reversi::OnMouse(HWND hwnd, Vector2 pos)
{
	if (state == STATE::PLAYER)//�v���C���[�̏����̏ꍇ
	{
		if (Put(hwnd, pos, WHITE))//�΂̐ݒu
		{
			//�I���`�F�b�N
			if (Win() != 0)
				state = STATE::RESULT;//���U���g�̊J�n
			else if(Board_PutCount(BLACK) != 0)
				state = STATE::NPC;//�^�[���̕ύX
			Draw(hwnd);
		}
	}

	if (state != STATE::RESULT)
	{
		//Pause�{�^��
		if (pauseButton.Contact(pos)) {
			state = STATE::PAUSE;//�|�[�Y��ԂɕύX
			Draw(hwnd);
		}
	}

	if (state == STATE::RESULT || state == STATE::PAUSE)
	{
		/*�@�@Result�{�^�������@�@*/
		if (buttons[0].Contact(pos))
			SendMessage(hwnd, WM_TITLE, 0, 0);//�^�C�g���ɖ߂�

		if (buttons[1].Contact(pos))
			Start(hwnd,level);//���g���C
	}
}

void Reversi::Draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	Draw_UI(hdc);
	Draw_Stage(hdc);

	if (state == STATE::RESULT)
		Draw_Result(hdc);

	if (state == STATE::PAUSE)
		Draw_Pause(hdc);
}