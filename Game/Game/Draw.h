#pragma once
#include <wchar.h>
#include "Game.h"
#include "Vector2.h"


class Draw
{
public:
	//テキスト
	static void Text(HDC hdc, Vector2 pos, int scale, LPCWSTR text, COLORREF textColor, COLORREF bkColor)
	{
		HFONT font = CreateFont(
			scale,                   // フォントの高さ(大きさ)。
			0,                    // フォントの幅。普通０。
			0,                    // 角度。０でＯＫ。
			0,                    // 同じく角度。これも０。
			FW_DONTCARE,          // 文字の太さ。
			FALSE,                // フォントがイタリックならTRUEを指定。
			FALSE,                // 下線を引くならTRUE。
			FALSE,                // 取り消し線を引くならTRUE。
			SHIFTJIS_CHARSET,     // フォントの文字セット。このままでＯＫ。
			OUT_DEFAULT_PRECIS,   // 出力精度の設定。このままでＯＫ。
			CLIP_DEFAULT_PRECIS,  // クリッピング精度。このままでＯＫ。
			DRAFT_QUALITY,        // フォントの出力品質。このままでＯＫ。
			DEFAULT_PITCH,        // フォントのピッチとファミリを指定。このままでＯＫ。
			L"明朝体");
		SelectObject(hdc, font);
		SetTextColor(hdc, textColor);  // 文字色を設定
		SetBkColor(hdc, bkColor);    // 背景色を設定

		int len = wcslen((LPCWSTR)text);
		SIZE size;
		GetTextExtentPoint32(hdc, text, len, &size);
		TextOut(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), text, lstrlen(text));
	}
	static void Text(HDC hdc, Vector2 pos, int scale, int textint, COLORREF textColor, COLORREF bkColor)
	{
		int buf_length = 256;
		wchar_t strlen[256];
		swprintf(strlen, buf_length, L"%02d", textint);

		HFONT font = CreateFont(
			scale,                   // フォントの高さ(大きさ)。
			0,                    // フォントの幅。普通０。
			0,                    // 角度。０でＯＫ。
			0,                    // 同じく角度。これも０。
			FW_DONTCARE,          // 文字の太さ。
			FALSE,                // フォントがイタリックならTRUEを指定。
			FALSE,                // 下線を引くならTRUE。
			FALSE,                // 取り消し線を引くならTRUE。
			SHIFTJIS_CHARSET,     // フォントの文字セット。このままでＯＫ。
			OUT_DEFAULT_PRECIS,   // 出力精度の設定。このままでＯＫ。
			CLIP_DEFAULT_PRECIS,  // クリッピング精度。このままでＯＫ。
			DRAFT_QUALITY,        // フォントの出力品質。このままでＯＫ。
			DEFAULT_PITCH,        // フォントのピッチとファミリを指定。このままでＯＫ。
			L"明朝体");
		SelectObject(hdc, font);
		SetTextColor(hdc, textColor);  // 文字色を設定
		SetBkColor(hdc, bkColor);    // 背景色を設定

		TextOut(hdc, pos.x, pos.y, (LPCWSTR)strlen, wcslen((LPCWSTR)strlen));
	}

	static void Text(HDC hdc, Vector2 pos, HFONT font,  LPCWSTR text, COLORREF textColor, COLORREF bkColor)
	{
		SelectObject(hdc, font);
		SetTextColor(hdc, textColor);  // 文字色を設定
		SetBkColor(hdc, bkColor);    // 背景色を設定

		int len = wcslen((LPCWSTR)text);
		SIZE size;
		GetTextExtentPoint32(hdc, text, len, &size);

		TextOut(hdc, pos.x  - (size.cx / 2), pos.y - (size.cy / 2), text, lstrlen(text));
	}

	//正四角形
	static void Square(HDC hdc, Vector2 center, int scale)
	{
		Rectangle(hdc, center.x - scale / 2, center.y + scale / 2, center.x + scale / 2, center.y - scale / 2);
	}
	static void Square(HDC hdc, Vector2 center, int scale, COLORREF color)
	{
		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
		Rectangle(hdc, center.x - scale / 2, center.y + scale / 2, center.x + scale / 2, center.y - scale / 2);
	}

	//四角形
	static void Square(HDC hdc, Vector2 leftUp, Vector2 rightDown)
	{
		Rectangle(hdc, leftUp.x, leftUp.y, rightDown.x, rightDown.y);
	}
	static void Square(HDC hdc, Vector2 leftUp, Vector2 rightDown, COLORREF color)
	{
		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
		Rectangle(hdc, leftUp.x, leftUp.y, rightDown.x, rightDown.y);
	}

	//円
	static void Circle(HDC hdc, Vector2 center, int scale)
	{
		Ellipse(hdc, center.x - scale / 2, center.y + scale / 2, center.x + scale / 2, center.y - scale / 2);
	}
	static void Circle(HDC hdc, Vector2 center, int scale, COLORREF color)
	{
		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
		Ellipse(hdc, center.x - scale / 2, center.y + scale / 2, center.x + scale / 2, center.y - scale / 2);
	}

	//線
	static void Line(HDC hdc, Vector2 start, Vector2 end)
	{
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);
	}
};