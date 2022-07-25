#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(int x, int y, short color, Direction eDirection, Entity* owner, double speed);
	Entity* GetOwner();

	void OnCollisionEntity(Entity* target) override;
	void Update() override;
private:
	Entity* owner;
};

#endif