#pragma once
#ifndef CANNON_H
#define CANNON_H

#include "Entity.h"

class Cannon : public Entity
{
public:
	Cannon(int x, int y, short color, Direction eDirection, double speed);
	void Update() override;
	void Shoot() override;
	void Kill(Entity*) override;
private:

};

#endif
