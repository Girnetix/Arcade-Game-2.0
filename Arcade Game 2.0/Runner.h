#pragma once
#ifndef RUNNER_H
#define RUNNER_H

#include "Entity.h"

class Runner : public Entity
{
public:
	Runner(int x, int y, short color, Direction eDirection, double speed);
	void OnCollisionEntity(Entity* target) override;
private:
	void Update() override;
};

#endif