#include "Game.h"

bool CGame::OnUserCreate()
{
	gameState = GameState::Running;
	world = new World();
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
	delete world;
}

void CGame::DoGameLoop(double deltaTime)
{
	/*fpscount++;
	gameTime += deltaTime;
	fpsTime -= deltaTime;
	if (fpsTime <= 0.0)
	{
		fpsTime += 1.0;
		pWindow->PrintMsg(10, 49, L"FPS: " + std::to_wstring(fpscount) + L" ", FG_RED);
		fpscount = 0;
	}
	int sec = gameTime;
	int min = sec / 60;
	int hour = min / 60;
	wchar_t msg[20];
	swprintf_s(msg, 20, L"%02d:%02d:%02d", hour, min % 60, sec % 60);
	pWindow->PrintMsg(0, 49, msg, FG_GREEN);*/
	world->UpdateWorld(deltaTime);
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
