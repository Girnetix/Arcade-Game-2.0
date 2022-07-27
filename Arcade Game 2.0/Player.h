#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player(int x, int y, short color, Direction eDirection, double speed, const std::wstring& name);
	Player& operator=(Player& other);
	void Update() override;
	void OnCollisionEntity(Entity* target) override;
	void Kill(Entity* killer);
private:
	void Shoot();
	void PrintDeathMsg(const std::wstring& msg);
private:
	double timeRespawn = 5.0;					//время возрождения в секундах
	double timeForRespawning = timeRespawn;
	int countOfBullets = 100;
	int maxCountOfBullets = 20;
	int id = 0;
	static int idCounter;
	std::wstring name = L"";
};

extern std::vector<Player*> playerList;

#endif