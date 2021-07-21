#pragma once

#include <vector>
#include <random>
#include <time.h>

#include "Button.h"
#include "Draw.h"
#include "Behaviour.h"

#define NONE   0//設置していない
#define WHITE  1//白
#define BLACK  2//黒

#define BOARD_LEFTUP Vector2(10,90)
#define BOARD_RIGHTDOWN Vector2(610, 690)

class Reversi :public Behaviour
{
	enum STATE { PLAYER, NPC, PAUSE, RESULT };
	//現在のボード
	int board[8][8] = {
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
				{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	};
	//評価
	int evaluation[8][8] = {
				{ 120 , -20 ,  20 ,   5 ,   5 ,  20 , -20 , 120 },
				{ -20 , -40 ,  -5 ,  -5 ,  -5 ,  -5 , -40 , -20 },
				{  20 ,  -5 ,  15 ,   3 ,   3 ,  15 ,  -5 ,  20 },
				{   5 ,  -5 ,   3 ,   3 ,   3 ,   3 ,  -5 ,   5 },
				{   5 ,  -5 ,   3 ,   3 ,   3 ,   3 ,  -5 ,   5 },
				{  20 ,  -5 ,  15 ,   3 ,   3 ,  15 ,  -5 ,  20 },
				{ -20 , -40 ,  -5 ,  -5 ,  -5 ,  -5 , -40 , -20 },
				{ 120 , -20 ,  20 ,   5 ,   5 ,  30 , -20 , 120 },
	};

	Button boardButton[8][8];
	STATE state;//現在の状態
	Button pauseButton;//ポーズ開始ボタン
	Button buttons[2];//1 = Titleに戻る 1 = Retryする
public:
	int level = 0;

	void Start(HWND, int);
	void Update(HWND);
	void OnMouse(HWND, Vector2);
	void Draw(HWND);

	//リセット
	void Reset()
	{
		//ボタンの設定
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++)
				boardButton[x][y] = Button(Vector2(
				(BOARD_LEFTUP.x + ((600 / 8) * x) + (600 / 8) / 2) - Vector2((600 / 8) / 2).x,
					(BOARD_LEFTUP.y + ((600 / 8) * y) + (600 / 8) / 2) - Vector2((600 / 8) / 2).y),
					Vector2(
						BOARD_LEFTUP.x + ((600 / 8) * x) + (600 / 8) / 2,
						BOARD_LEFTUP.y + ((600 / 8) * y) + (600 / 8) / 2)
					+ Vector2((600 / 8) / 2));
		}

		//ポーズ
		pauseButton = Button(Vector2(10, 10), Vector2(200, 80), RGB(204, 204, 153));

		//リザルトのボタンの設定
		buttons[0] = Button(Vector2(80, 350), Vector2(320, 450), RGB(153, 204, 255));
		buttons[1] = Button(Vector2(480, 350), Vector2(720, 450), RGB(153, 204, 255));

		//すべて0にする
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++)
				board[x][y] = NONE;
		}

		//中心に石を置く
		board[3][3] = WHITE;
		board[4][3] = BLACK;
		board[3][4] = BLACK;
		board[4][4] = WHITE;
	}

	//UIの描写
	void Draw_UI(HDC hdc)
	{
		COLORREF c_num = RGB(0, 0, 255);
		COLORREF c_black = RGB(0, 0, 0);
		COLORREF c_back = RGB(204, 204, 204);

		Draw::Square(hdc, Vector2(0, 0), Vector2(800, 700), c_back);

		Draw::Text(hdc, Vector2(500, 50), 90, L"REVERSI", RGB(0, 0, 0), c_back);
		//白の数
		Draw::Text(hdc, Vector2(700, 560), 40, L"自分の数", RGB(0, 0, 0), c_back);
		Draw::Square(hdc, Vector2(620, 590), Vector2(790, 690), c_num);
		Draw::Text(hdc, Vector2(620 + 10, 590 + 10), 80, Board_Count(WHITE), c_black, c_num);
		//黒の数
		Draw::Text(hdc, Vector2(700, 360), 40, L"相手の数", RGB(0, 0, 0), c_back);
		Draw::Square(hdc, Vector2(620, 390), Vector2(790, 490), c_num);
		Draw::Text(hdc, Vector2(620 + 10, 390 + 10), 80, Board_Count(BLACK), c_black, c_num);


		Draw::Text(hdc, Vector2(740, 280), 30, L"のターン", c_black, c_back);
		Draw::Circle(hdc, Vector2(700, 200), 120, state == STATE::PLAYER ? RGB(250, 250, 250) : RGB(0, 0, 0));

		pauseButton.Draw(hdc, L"Pause", 60, RGB(0, 0, 0));
	}
	//ステージの描写
	void Draw_Stage(HDC hdc)
	{
		COLORREF c_black = RGB(0, 0, 0);
		COLORREF c_white = RGB(255, 255, 255);

		COLORREF c_board = RGB(0, 128, 0);

		Draw::Square(hdc, BOARD_LEFTUP, BOARD_RIGHTDOWN, c_board);
		////ステージ描写
		for (int i = 1; i < 8; i++)
		{
			Draw::Line(hdc,
				Vector2(BOARD_LEFTUP.x + ((600 / 8) * i), BOARD_LEFTUP.y),
				Vector2(BOARD_LEFTUP.x + ((600 / 8) * i), BOARD_RIGHTDOWN.y));

			Draw::Line(hdc,
				Vector2(BOARD_LEFTUP.x, BOARD_LEFTUP.y + +((600 / 8) * i)),
				Vector2(BOARD_RIGHTDOWN.x, BOARD_LEFTUP.y + +((600 / 8) * i)));
		}

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++)
				if (board[x][y] != NONE)
					Draw::Circle(hdc, Vector2(
						BOARD_LEFTUP.x + ((600 / 8) * x) + (600 / 8) / 2,
						BOARD_LEFTUP.y + ((600 / 8) * y) + (600 / 8) / 2),
						60, board[x][y] == WHITE ? c_white : c_black);
		}
	}
	//Pause時の描写
	void Draw_Pause(HDC hdc)
	{
		Draw::Text(hdc, Vector2(800, 700) / 2 + Vector2(0, -100), 100, L"PAUSE", RGB(0, 0, 0), RGB(250, 250, 250));
		buttons[0].Draw(hdc, L"タイトル", 50, RGB(250, 250, 250));
		buttons[1].Draw(hdc, L"リトライ", 50, RGB(250, 250, 250));
	}
	//リザルト時の描写
	void Draw_Result(HDC hdc)
	{
		Draw::Text(hdc, Vector2(800, 700) / 2 + Vector2(0, -100), 100, L"RESULT", RGB(0, 0, 0), RGB(250, 250, 250));
		buttons[0].Draw(hdc, L"タイトル", 50, RGB(250, 250, 250));
		buttons[1].Draw(hdc, L"リトライ", 50, RGB(250, 250, 250));
	}

	//設置する 設置したらtrue
	bool Put(HWND hwnd, Vector2 pos, int no)
	{
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				//石を置けるか判定
				if (boardButton[x][y].Contact(pos) && Board_PutChack(x, y, no)) {
					//boardButton[x][y]をplayNoに変更
					Board_Change(x, y, no);

					SendMessage(hwnd, WM_PAINT, 0, 0);//PAINTの再読み込み
					return true;
				}
			}
		}
		return false;
	}
	//敵の設置処理　設置したらtrue
	bool Npc(HWND hwnd, int n, int level)//敵の設置
	{
		///初級　一番評価が低い場所に置く
		if (level == 1)
		{
			int scoar = 200;
			Vector2 put;
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (Board_PutChack(x, y, n))
					{
						if (scoar >= evaluation[x][y])
						{
							scoar = evaluation[x][y];
							put = Vector2(x, y);
						}
					}
				}
			}

			Board_Change(put.x, put.y, n);
			return true;
		}
		///中級　ランダムに置く
		else if (level == 2)
		{
			OutputDebugString(L"PUTEEDFDESA");
			int count = 0;
			Vector2 v[64] = {};
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (Board_PutChack(x, y, n)) {
						v[count] = Vector2(x,y);
						count++;
					}
				}
			}
			srand(time(NULL));//乱数の初期化
			Vector2 r = v[rand() % count];
			Board_Change(r.x, r.y, n);//石を置く
			return true;
		}
		///上級　評価が一番高い場所に置く
		else if (level == 3)
		{
			int scoar = -200;
			Vector2 put;
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (Board_PutChack(x, y, n))
					{
						if (scoar <= evaluation[x][y])
						{
							scoar = evaluation[x][y];
							put = Vector2(x, y);
						}
					}
				}
			}

			Board_Change(put.x, put.y, n);
			return true;
		}

		return false;
	}


	//board[x][y]にnを入れられるか確認
	bool Board_PutChack(int x, int y, int n)
	{
		//相手の色
		int e = (n == WHITE ? BLACK : WHITE);
		if (board[x][y] != NONE)return false;

		for (int _x = -1; _x < 2; _x++) {
			for (int _y = -1; _y < 2; _y++) {

				if (_x == 0 && _y == 0)
					continue;

				if (x + _x > 7 || x + _x < 0 || y + _y > 7 || y + _y < 0)//隣が範囲外じゃないか
					continue;

				if (board[x + _x][y + _y] != e)//隣が相手の色かどうか
					continue;

				for (int i = 2; i < 8; i++)
				{
					if (x + (_x * i) > 7 || x + (_x * i) < 0 || y + (_y * i) > 7 || y + (_y * i) < 0)  break;
					else if (board[x + (_x * i)][y + (_y * i)] == NONE) break;
					else if (board[x + (_x * i)][y + (_y * i)] == n) return true;
				}
			}
		}
		return false;
	}
	//石の設置＆裏返す
	void Board_Change(int x, int y, int n) {

		int e = (n == WHITE ? BLACK : WHITE);
		//石の判定処理
		board[x][y] = n;
		for (int _x = -1; _x < 2; _x++) {
			for (int _y = -1; _y < 2; _y++) {
				//vector2 (x,y)方向を審査

				int count = 1;
				//中心は行わない
				if (_y == 0 && _x == 0)
					continue;
				//範囲内かどうか
				if (x + _x > 7 || x + _x < 0 || y + _y > 7 || y + _y < 0)//隣が範囲外じゃないか
					continue;

				if (board[x + _x][y + _y] != e)//隣が相手の色かどうか
					continue;

				for (int i = 2; i < 8; i++)
				{
					if (x + (_x * i) > 7 || x + (_x * i) < 0 || y + (_y * i) > 7 || y + (_y * i) < 0)  break;
					else if (board[x + (_x * i)][y + (_y * i)] == NONE) break;
					else if (board[x + (_x * i)][y + (_y * i)] == e)count++;
					else if (board[x + (_x * i)][y + (_y * i)] == n) {
						for (int c = 0; c < count + 1; c++)
							board[x + (_x * c)][y + (_y * c)] = n;
					}
				}
			}
		}

	}
	//ボードの数の取得
	int Board_Count(int n)
	{
		int c = 0;
		for (int x = 0; x < 8; x++)
			for (int y = 0; y < 8; y++)
				if (board[x][y] == n)
					c++;
		return c;
	}
	//置く場所の数を返す
	int Board_PutCount(int n)
	{
		int count = 0;

		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				count += Board_PutChack(x, y, n) == true ? 1 : 0;
			}
		}
		return count;
	}
	//終了状態を返す
	int Win() {
		if (Board_Count(NONE) == 0 || Board_Count(WHITE) == 0 || Board_Count(BLACK) == 0)
			return Board_Count(WHITE) == Board_Count(BLACK) ? 3 : Board_Count(BLACK) > Board_Count(WHITE) ? BLACK : WHITE;
		return 0;//未勝利状態
	}
};