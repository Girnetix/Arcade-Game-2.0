#pragma once
#ifndef CANNON_H
#define CANNON_H

#include "Entity.h"

class Cannon : public Entity
{
public:
	Cannon(int x, int y, short color, Direction eDirection, double speed);
	void OnCollisionEntity(Entity* target) override;
	void Update() override;
private:
	void Shoot();
};

#endif
