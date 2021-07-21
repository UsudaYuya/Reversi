#pragma once
#include <wchar.h>
#include "Game.h"
#include "Vector2.h"


class Draw
{
public:
	//�e�L�X�g
	static void Text(HDC hdc, Vector2 pos, int scale, LPCWSTR text, COLORREF textColor, COLORREF bkColor)
	{
		HFONT font = CreateFont(
			scale,                   // �t�H���g�̍���(�傫��)�B
			0,                    // �t�H���g�̕��B���ʂO�B
			0,                    // �p�x�B�O�łn�j�B
			0,                    // �������p�x�B������O�B
			FW_DONTCARE,          // �����̑����B
			FALSE,                // �t�H���g���C�^���b�N�Ȃ�TRUE���w��B
			FALSE,                // �����������Ȃ�TRUE�B
			FALSE,                // ���������������Ȃ�TRUE�B
			SHIFTJIS_CHARSET,     // �t�H���g�̕����Z�b�g�B���̂܂܂łn�j�B
			OUT_DEFAULT_PRECIS,   // �o�͐��x�̐ݒ�B���̂܂܂łn�j�B
			CLIP_DEFAULT_PRECIS,  // �N���b�s���O���x�B���̂܂܂łn�j�B
			DRAFT_QUALITY,        // �t�H���g�̏o�͕i���B���̂܂܂łn�j�B
			DEFAULT_PITCH,        // �t�H���g�̃s�b�`�ƃt�@�~�����w��B���̂܂܂łn�j�B
			L"������");
		SelectObject(hdc, font);
		SetTextColor(hdc, textColor);  // �����F��ݒ�
		SetBkColor(hdc, bkColor);    // �w�i�F��ݒ�

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
			scale,                   // �t�H���g�̍���(�傫��)�B
			0,                    // �t�H���g�̕��B���ʂO�B
			0,                    // �p�x�B�O�łn�j�B
			0,                    // �������p�x�B������O�B
			FW_DONTCARE,          // �����̑����B
			FALSE,                // �t�H���g���C�^���b�N�Ȃ�TRUE���w��B
			FALSE,                // �����������Ȃ�TRUE�B
			FALSE,                // ���������������Ȃ�TRUE�B
			SHIFTJIS_CHARSET,     // �t�H���g�̕����Z�b�g�B���̂܂܂łn�j�B
			OUT_DEFAULT_PRECIS,   // �o�͐��x�̐ݒ�B���̂܂܂łn�j�B
			CLIP_DEFAULT_PRECIS,  // �N���b�s���O���x�B���̂܂܂łn�j�B
			DRAFT_QUALITY,        // �t�H���g�̏o�͕i���B���̂܂܂łn�j�B
			DEFAULT_PITCH,        // �t�H���g�̃s�b�`�ƃt�@�~�����w��B���̂܂܂łn�j�B
			L"������");
		SelectObject(hdc, font);
		SetTextColor(hdc, textColor);  // �����F��ݒ�
		SetBkColor(hdc, bkColor);    // �w�i�F��ݒ�

		TextOut(hdc, pos.x, pos.y, (LPCWSTR)strlen, wcslen((LPCWSTR)strlen));
	}

	static void Text(HDC hdc, Vector2 pos, HFONT font,  LPCWSTR text, COLORREF textColor, COLORREF bkColor)
	{
		SelectObject(hdc, font);
		SetTextColor(hdc, textColor);  // �����F��ݒ�
		SetBkColor(hdc, bkColor);    // �w�i�F��ݒ�

		int len = wcslen((LPCWSTR)text);
		SIZE size;
		GetTextExtentPoint32(hdc, text, len, &size);

		TextOut(hdc, pos.x  - (size.cx / 2), pos.y - (size.cy / 2), text, lstrlen(text));
	}

	//���l�p�`
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

	//�l�p�`
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

	//�~
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

	//��
	static void Line(HDC hdc, Vector2 start, Vector2 end)
	{
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);
	}
};