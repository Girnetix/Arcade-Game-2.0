#include "MenuCreater.h"

Menu* pMenu = nullptr;

Menu* Menu::root = nullptr;
Menu* Menu::currentState = nullptr;
std::wstring Menu::lastTarget = L"";

Menu::Menu()
{
	title = L"main";
	subTitle = L"";
	root = currentState = this;
	parent = nullptr;
	active = true;
}

Menu::Menu(std::wstring title, Menu* parent)
{
	this->title = title;
	this->parent = parent;
	active = true;
}

Menu::~Menu()
{
	children.clear();
}

void Menu::Active(bool isActive)
{
	this->active = isActive;
}

void Menu::AddSubTitle(std::wstring subTitle)
{
	this->subTitle = subTitle;
}

void Menu::DrawMenu(Window* window)
{
	window->ClearAllWindow();
	//currentState = FindMenuObject(lastTarget, root);

	int counter = 0;
	for (auto& current : currentState->children)
	{
		if (counter == 0)
			cursor.yMin = window->GetScrHeight() / 2 - currentState->children.size() / 2 + counter;
		else if(counter == currentState->children.size())
			cursor.yMax = window->GetScrHeight() / 2 - currentState->children.size() / 2 + counter;

		if (current.active)
			window->PrintMsgInCenter(window->GetScrHeight() / 2 - currentState->children.size() / 2 + counter++, current.title);
		else
			window->PrintMsgInCenter(window->GetScrHeight() / 2 - currentState->children.size() / 2 + counter++, current.title, FG_GREY | BG_BLACK);
	}	
	//lastTarget = cursor.drawCursor(window);
}

Menu* Menu::FindMenuObject(std::wstring title, Menu* parent)
{
	for (auto &current : parent->children)
	{
		if (current.title == title)
			return (Menu*)&current;
		else if (current.children.size())
		{
			Menu* result = FindMenuObject(title, (Menu*)&current);
			if (result != nullptr)
				return result;
		}
	}
	return nullptr;
}

Menu& Menu::operator[](std::wstring title)
{
	if (children.size())							//если есть наследники
		for (auto& current : children)		//перебираем наследников
			if (current.title == title)		//если находим наследника с текущим именем, то возвращаем его
				return current;
	children.emplace_back(title, this);				//если не существует наследника с таким именем, то добавляем его к текущему предку
	return *this;									//возвращаем предка
}

std::wstring Menu::Cursor::drawCursor(Window* window)
{
	if (firstDraw)
	{
		yPos = yMin;
		firstDraw = false;
	}

	return std::wstring();
}
