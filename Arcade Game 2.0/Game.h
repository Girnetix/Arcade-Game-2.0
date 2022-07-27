#pragma once
#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "World.h"

class CGame: public CEngine
{
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void OnUserDestroy() override;
	void DoGameLoop(double deltaTime);
private:
	enum class GameState
	{
		Menu,
		Editor,
		Hints,
		Running,
		Paused,
	};
private:
	GameState gameState = GameState::Menu;			//состояние игры
	bool gameIsRunning = true;		//переменная, которая показывает запущена игра или нет
	double gameTime = 0.0, fpsTime = 1.0, minFPS = 0.0, maxFPS = 0.0;
	int fpscount = 0;
};

#endif
