#pragma once
#ifndef RENDER_H
#define RENDER_H

#include<Windows.h>
#include<string>

enum Color
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007,
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};
enum CursVis
{
	VISIBLE,
	INVISIBLE
};

class Window
{
public:
	Window();
	~Window();

	void PrintSymbol(int x, int y, short ch, short color = FG_WHITE | BG_BLACK);
	void ClearSymbol(int x, int y, const wchar_t msg);
	void ConstructWindow(int width, int height, const std::wstring& nameApp);
	void PrintMsg(int x, int y, const std::wstring& msg, short color = FG_WHITE | BG_BLACK);
	void PrintMsgInCenter(int y, const std::wstring& msg, short color = FG_WHITE | BG_BLACK);
	void PrintSymbol(int x, int y, const wchar_t msg, short color = FG_WHITE | BG_BLACK);
	void ClearMsg(int x, int y, const std::wstring& msg);
	void ClearMsgInCenter(int y, const std::wstring& msg);
	void ChangeAppNme(const std::wstring& nameApp);
	void AddToAppName(const std::wstring& str);
	void UpdateWindow();
	void CloseWindow();
	void ClearAllWindow();
	void CursorVisible(int value);

	int GetScrWidth();
	int GetScrHeight();

	wchar_t GetChar(int x, int y);
	std::wstring TextMode(int posX, int posY);
protected:
	CHAR_INFO* screen = nullptr;
	int screenWidth, screenHeight;
	int cursX, cursY;
	std::wstring AppName;
	HANDLE hConsole;
	SMALL_RECT rectWindow;
};

extern Window* pWindow;

#endif