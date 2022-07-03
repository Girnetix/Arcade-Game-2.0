#include "Game.h"

bool CGame::OnUserCreate()
{
	gameState = GameState::Running;
	
	return true;
}

bool CGame::OnUserUpdate(float fElapsedTime)
{
	switch (gameState)
	{
		case CGame::GameState::Menu:	pMenu->DrawMenu(pWindow); break;
		case CGame::GameState::Editor:	break;
		case CGame::GameState::Hints:	break;
		case CGame::GameState::Running: DoGameLoop(fElapsedTime); break;
		case CGame::GameState::Paused:	break;
	}	

	return gameIsRunning;
}

void CGame::OnUserDestroy()
{
	
}

void CGame::DoGameLoop(double deltaTime)
{
	//int count = entities.size();							//текущее кол-во объектов

	//for (int i = 0; i < count; i++)
	//{
	//	entities[i]->UpdateEntity(deltaTime);
	//	if (count - (int)entities.size() == -1)			//если после обновления объекта изменилось общее кол-во объектов
	//	{
	//		count = entities.size();
	//		i--;
	//	}
	//}
		
}
