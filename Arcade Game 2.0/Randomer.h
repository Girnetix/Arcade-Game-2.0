#pragma once
#ifndef RANDOMER_H
#define RANDOMER_H

#include "Entity.h"

class Randomer : public Entity
{
public:
	Randomer(int x, int y, short color, double speed);
	void Update() override;
	void Shoot() override;
	void Kill(Entity*) override;
private:

};

#endif