#include "Game.h"
#include "Draw.h"

#include "Behaviour.h"
#include "Title.h"
#include "Reversi.h"

#include <iostream>
#include <vector>

int Scene;

Behaviour* behaviour;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool Game::Initialize(LPCWSTR windowTitle, int screenWidth, int screenHeight)
{
	//ウィンドウのタイトル
	WindowTitle = windowTitle;
	//ウィンドウの幅
	ScreenWidth = screenWidth;
	//ウィンドウの高さ
	ScreenHeight = screenHeight;
	//タイトルシーン
	Scene = SCENE_TITLE;

	return true;
}

bool Game::InitWindow()
{
	//ロードされているモジュールのハンドルをhInstanceに入れる
	HINSTANCE hInstance = GetModuleHandle(NULL);

	//ウィンドウクラスの登録 wchaar_t:ワイド文字型
	const wchar_t CLASS_NAME[] = L"GameWindow";
	//WNDCLASSEX:ウィンドクラスのパラメーター
	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(WNDCLASSEX);//構造体のサイズ　ウィンドウスタイル
	//ウィンドウのメッセージを処理するコールバック関数へのポインタ
	wndClass.lpfnWndProc = WindowProc;
	//このクラスのためのウインドウプロシージャがあるインスタンスハンドル．
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//マウスカーソルのハンドル
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);;//ウィンドウ背景色　HBRUSH:背景色のクラス?
	wndClass.lpszClassName = CLASS_NAME;//このウインドウクラスにつける名前

	if (!RegisterClassEx(&wndClass)) {
		return false;
	}

	//クライアント領域の短径
	RECT rect = { 0,0,ScreenWidth,ScreenHeight };
	//クライアント領域が指定した解像度になるウィンドウサイズを計算　FALSE:ウィンドウがメニューともつかどうか　0:拡張スタイル
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);


	//Windowを作成する
	hWnd = CreateWindowEx(
		0,//拡張ウィンドウのスタイルを設定する値　CreateWindowEx/SetWindowLongのパラメーター　GetWindowLongの戻り値
		CLASS_NAME,//ウィンドウクラスの名前を表す文字列
		WindowTitle,//ウィンドウ名を表す文字列へのポインタを指定
		//WS_OVERLAPPEDWINDOW WS_OVERLAPPED, WS_CAPTION, WS_SYSMENU, WS_THICKFRAME, WS_MINIMIZEBOX, WS_MAXIMIZEBOXスタイルを持つオーバーラップウィンドウを作成します
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE,//作成されるウィンドウスタイル サイズ固定
		CW_USEDEFAULT,//デフォルトのウィンドウの位置の設定
		CW_USEDEFAULT,//　　　　　　　〃
		(rect.right - rect.left),//ウィンドウの幅
		(rect.bottom - rect.top),//ウィンドウの高さ
		NULL,//作成中のウィンドウの親ウィンドウまた所有者ウィンドウへのハンドル
		NULL,//ウィンドウスタイルに応じて、メニューへのハンドル、または子ウィンドウ識別子を指定
		hInstance,//ウィンドウに関連付けられるモジュールのインスタンスへのハンドル。
		NULL);//窓に渡される値を指すポインタCREATESTRUCTの構造によって指されたlParamののPARAM WM_CREATEのメッセージ

	if (hWnd == NULL)//Windowが存在場合
		return false;//終了

	//hWnd:表示状態を変更するウィンドウのハンドル SW_SHOWNOMAL:ウィンドウをアクティブにして表示
	ShowWindow(hWnd, SW_SHOWNORMAL);// ウィンドウを表示

	//WM_PAINTが空ではない場合メッセージを送る
	UpdateWindow(hWnd);//hWnd:更新するウィンドウハンドル

	///-------------------------------
	/// 初期稼働クラス
	///-------------------------------
	behaviour = new Title();
	behaviour->Start(hWnd);
	SendMessage(hWnd, WM_PAINT, 0, 0);//PAINTの再読み込み

	return true;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	*WM_CREATE		:Window生成時
	*WM_DESTROY		:Windo破棄時
	*WM_MOVE		:Window移動時
	*WM_SIZE		:Windowサイズ変更時
	*WM_PAINT		:再描画の必要時
	*WM_CLOSE		:終了が選択されたとき
	*WM_QUIT		:PostQuitmessage関数の実行時 PostQuitmessage:スレッドが終了を要求したときをシステムに伝える
	*WM_KEYDOWN		:非システムキーが押されたとき
	*WM_KEYUP		:非システムキーが開放されたとき
	*WM_MOUSEMOVE	:マウスの移動時
	*WM_LBUTTONDOWN	:左マウスボタンが押されたとき
	*WM_LBUTTONUP	:左マウスボタンの解放時
	*/
	HDC hdc;
	PAINTSTRUCT ps;

	switch (uMsg)
	{
	case WM_CLOSE:
	{
		// ウィンドウを閉じる
		if (MessageBox(hWnd, L"ウィンドウを閉じますか？", L"メッセージ", MB_OKCANCEL) == IDOK) {
			DestroyWindow(hWnd);
		}
	}
	return 0;

	case WM_DESTROY:
	{
		PostQuitMessage(0);// アプリケーションを終了
	}

	case WM_LBUTTONDOWN:
	{
		behaviour->OnMouse(hWnd, Vector2(LOWORD(lParam), HIWORD(lParam)));
	}
	return 0;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		if (behaviour != NULL)
			behaviour->Draw(hWnd);

		EndPaint(hWnd, &ps);
	}
	return 0;

	//タイトルの開始
	case WM_TITLE:
	{
		Scene = SCENE_RESULT;
		behaviour = new Title();
		behaviour->Start(hWnd);
		SendMessage(hWnd, WM_PAINT, 0, 0);//PAINTの再読み込み
	}
	return 0;

	case WM_REVERSI:
	{
		Scene = SCENE_REVERSI;
		behaviour = new Reversi();
		behaviour->Start(hWnd, wParam);
		SendMessage(hWnd, WM_PAINT, 0, 0);//PAINTの再読み込み
	}
	return 0;
	}
	//プロシージャ―の因数の入力をすることで自動で処理を行い終了コードを出してくれる関数
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Game::Run()
{
	if (!InitWindow())//ウィンドウの作成
	{
		MessageBox(NULL, L"ウィンドウの作成に失敗しました", L"エラー", MB_OK);
	}
	//hwnd:Windowハンドル iparam:メッセージの追加情報を指定する massage:メッセージID
	//pt_x/y:ポストされたときのカーソルx/y time:ポストされた時刻 wparam:メッセージの追加情報
	//ポスト=投稿される
	MSG msg{};

	HDC hdc = GetDC(hWnd);
	while (true)
	{
		//プログラムにメッセージが送られているか確認
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))//メッセージ処理
				break;

			TranslateMessage(&msg);//仮想キーを文字コードにしてメッセージキューにポストする
			//ディスパッチ = 発送派遣する　データの送信
			DispatchMessage(&msg);//ウィンドウプロシージャにメッセージをディスパッチ
		}

		behaviour->Update(hWnd);
	}
}
