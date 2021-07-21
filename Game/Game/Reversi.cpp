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
	Reset();//石のリセットとボタンの設定
	Draw(hwnd);
}

void Reversi::Update(HWND hwnd)
{
	if (state == STATE::NPC)//
	{
		Sleep(1000);//待機
		if (Npc(hwnd, BLACK, level))
		{
			//終了チェック
			if (Win() != 0)
				state = STATE::RESULT;//リザルトの開始
			else {
				if (Board_PutCount(WHITE) != 0)
					state = STATE::PLAYER;//ターンの変更
			}
			Draw(hwnd);
		}
	}
}

void Reversi::OnMouse(HWND hwnd, Vector2 pos)
{
	if (state == STATE::PLAYER)//プレイヤーの処理の場合
	{
		if (Put(hwnd, pos, WHITE))//石の設置
		{
			//終了チェック
			if (Win() != 0)
				state = STATE::RESULT;//リザルトの開始
			else if(Board_PutCount(BLACK) != 0)
				state = STATE::NPC;//ターンの変更
			Draw(hwnd);
		}
	}

	if (state != STATE::RESULT)
	{
		//Pauseボタン
		if (pauseButton.Contact(pos)) {
			state = STATE::PAUSE;//ポーズ状態に変更
			Draw(hwnd);
		}
	}

	if (state == STATE::RESULT || state == STATE::PAUSE)
	{
		/*　　Resultボタン処理　　*/
		if (buttons[0].Contact(pos))
			SendMessage(hwnd, WM_TITLE, 0, 0);//タイトルに戻る

		if (buttons[1].Contact(pos))
			Start(hwnd,level);//リトライ
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