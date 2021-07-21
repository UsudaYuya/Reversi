#pragma once
#include "Behaviour.h"
#include "Draw.h"
#include "Button.h"

///----------------------------------
///　　　　オセロの開始
///----------------------------------
class Title :public Behaviour
{
	Button startButton[3];

	HFONT title;

public:
	void Start(HWND hWnd)
	{
		startButton[0] = Button(Vector2(450, 120), Vector2(450 + 320, 120 + 100), RGB(204, 204, 153));
		startButton[1] = Button(Vector2(450, 120 + (700 / 3)), Vector2(450 + 320, 120 + 100 + (700 / 3)), RGB(204, 204, 153));
		startButton[2] = Button(Vector2(450, 120 + (700 / 3) * 2), Vector2(450 + 320, 120 + 100 + (700 / 3) * 2), RGB(204, 204, 153));
		//タイトルロゴ
		title = CreateFont(100, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, L"Impact");
	}

	void Draw(HWND hWnd)
	{
		//HDC hdc = GetDC(hWnd);
		HDC hdc = GetDC(hWnd);

		COLORREF c_BG = RGB(100, 100, 100);//背景色
		COLORREF c_REVERSI = RGB(0, 128, 0);//リバーシ背景　左
		COLORREF c_CENTER = RGB(128, 0, 128);//〇〇背景　左
		COLORREF c_RIGHT = RGB(0, 128, 128);//〇〇背景　左

		COLORREF t_ROGO = RGB(0, 0, 0);//タイトル色
		COLORREF t_BUTTON = RGB(250, 250, 250);//タイトル色

		Draw::Square(hdc, Vector2(0, 0), Vector2(800, 700), c_BG);	//背景

		Draw::Square(hdc, Vector2(200, 0), Vector2(800, 700 / 3), c_REVERSI);	//左　リバーシ
		Draw::Square(hdc, Vector2(200, 700 / 3), Vector2(800 * 2, 700 / 3 * 2), c_CENTER);	//中　リバーシ
		Draw::Square(hdc, Vector2(200, 700 / 3 * 2), Vector2(800, 700), c_RIGHT);	//右　リバーシ

		//タイトルテキスト
		Draw::Text(hdc, Vector2(100, 50 + 000), title, L"R", t_ROGO, c_BG);
		Draw::Text(hdc, Vector2(100, 50 + 100), title, L"E", t_ROGO, c_BG);
		Draw::Text(hdc, Vector2(100, 50 + 200), title, L"V", t_ROGO, c_BG);
		Draw::Text(hdc, Vector2(100, 50 + 300), title, L"E", t_ROGO, c_BG);
		Draw::Text(hdc, Vector2(100, 50 + 400), title, L"R", t_ROGO, c_BG);
		Draw::Text(hdc, Vector2(100, 50 + 500), title, L"S", t_ROGO, c_BG);
		Draw::Text(hdc, Vector2(100, 50 + 600), title, L"I", t_ROGO, c_BG);

		//テキスト
		Draw::Text(hdc, Vector2(300 + 10, 70), 100, L"初級", t_ROGO, c_REVERSI);
		Draw::Text(hdc, Vector2(300 + 10, 70 + (700 / 3)), 100, L"中級", t_ROGO, c_CENTER);
		Draw::Text(hdc, Vector2(300 + 10, 70 + (700 / 3) * 2), 100, L"上級", t_ROGO, c_RIGHT);
		//ボタン
		for (int i = 0; i < 3; i++)
			startButton[i].Draw(hdc,L"スタート",60,RGB(0,0,0));
	}

	void OnMouse(HWND hWnd, Vector2 mouse)
	{
		//初級
		if (startButton[0].Contact(mouse))
			SendMessage(hWnd, WM_REVERSI, 1, 0);//PAINTの再読み込み
		//中級
		else if (startButton[1].Contact(mouse))
			SendMessage(hWnd, WM_REVERSI, 2, 0);//PAINTの再読み込み
		//上級
		else if (startButton[2].Contact(mouse))
			SendMessage(hWnd, WM_REVERSI, 3, 0);//PAINTの再読み込み		
	}
};