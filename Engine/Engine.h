#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "Network.h"
#include "Rendering.h"
#include "Timer.h"
#include "FileSystem.h"
#include "PRNG.h"
#include "MenuCreater.h"
#include "Input.h"

class CEngine
{
private:
	void GameThread();
public:
	void Start(int ScreenWidth, int ScreenHeight, std::wstring NameApp);
	void Stop();
protected:
	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float fElapsedTime) = 0;
	virtual void OnUserDestroy() = 0;
private:
	bool bIsRunning = false;
protected:
	bool bShowFPS = false;
	bool bShowPing = false;
};

#endif