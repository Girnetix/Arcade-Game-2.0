#pragma once
#ifndef RUNNER_H
#define RUNNER_H

#include "Entity.h"

class Runner : public Entity
{
public:
	Runner(int x, int y, short color, Direction eDirection, double speed);
	void Update() override;
	void Shoot() override;
	void Kill(Entity*) override;
private:

};

#endif