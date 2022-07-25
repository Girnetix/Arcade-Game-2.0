#pragma once
#ifndef CHASER_H
#define CHASER_H

#include "Entity.h"

class Chaser : public Entity
{
public:
	Chaser(int x, int y, short color, Direction eDirection, double speed);
	void Update() override;
	void OnCollisionEntity(Entity* target) override;
private:
	Entity* FindPlayer();
private:
	Entity* targetPlayer = nullptr;
	int maxDistance = 5;
};

#endif
