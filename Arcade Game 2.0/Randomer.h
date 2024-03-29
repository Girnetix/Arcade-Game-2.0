#pragma once
#ifndef RANDOMER_H
#define RANDOMER_H

#include "Entity.h"

class Randomer : public Entity
{
public:
	Randomer(int x, int y, int minX, int minY, int maxX, int maxY, short color, double speed);
	void OnCollisionEntity(Entity* target) override;
private:
	void Update() override;
	int minX = 0, maxX = 0, minY = 0, maxY = 0;
};

#endif