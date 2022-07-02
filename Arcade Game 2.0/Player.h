#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player(int x, int y, short color, Direction eDirection, double speed, const std::wstring& name);
	void Update() override;
	void Shoot() override;
	void Kill(Entity* killer) override;
	void PrintDeathMsg(const std::wstring& msg);
private:
	int timeRespawn = 5;					//время возрождения в секундах
	int countOfBullets = 100;
	int maxCountOfBullets = 20;
	int id = 0;
	static int X, Y;
	static int idCounter;
	std::wstring name = L"";
};

#endif