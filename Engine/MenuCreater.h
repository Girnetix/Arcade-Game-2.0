#pragma once
#ifndef MENU_H
#define MENU_H

#include "Rendering.h"
#include <vector>

class Menu
{
public:
	Menu();
	Menu(std::wstring title, Menu* parent);
	~Menu();
	void Active(bool isActive);
	void AddSubTitle(std::wstring subTitle);
	void DrawMenu(Window* window);
	Menu* FindMenuObject(std::wstring title, Menu* parent);
	Menu& operator[](std::wstring title);
private:
	class Cursor
	{
	public:
		std::wstring drawCursor(Window* window);
	public:
		std::wstring lCurs = L"->", rCurs = L"<-";
		int yPos = 0, yMin = 0, yMax = 0;
		bool firstDraw = true;
	};
private:
	std::wstring title;
	std::wstring subTitle;
	std::vector<Menu> children;
	Cursor cursor;
	Menu* parent;
	bool active;
private:
	static Menu* root;
	static Menu* currentState;
	static std::wstring lastTarget;
};

extern Menu* pMenu;

#endif
