#include "Game.h"

int main()
{
	CGame* pGame = new CGame();
	pGame->Start(120, 50, L"�������� ����");

	delete pGame;
	return 0;
}