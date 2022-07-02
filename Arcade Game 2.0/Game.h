#pragma once
#ifndef GAME_H
#define GAME_H

#include "World.h"

class CGame: public CEngine
{
private:
	void DoGameLoop(double deltaTime);
private:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void OnUserDestroy() override;
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
	double gameTime = 0.0, fpsTime = 1.0, minFPS = 0.0, maxFPS = 0.0, currentFPS = 0.0;
};

#endif
