#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <Engine/Engine.h>
#include <vector>

class Entity
{
public:
	enum class Direction { Up = 24, Down, Left, Right };
	enum class EntityType{ Player, Bullet, Cannon, Runner, Randomer, Chaser, MovableEntity, CheckPoint, Health, Ammo, Life };
public:
	Entity();
	Entity(int x, int y, short color, Direction eDirection, double speed);


	void DestroyEntity(Entity* entity);

	int GetX();
	int GetY();

	void Alive(bool isAlive);
	bool IsAlive();

	void UpdateEntity(double deltaTime);

	Entity* GetEntity(int x, int y);

	EntityType GetEntityType();
	Direction GetDiretion();
public:
	virtual void Update() = 0;
	virtual void Shoot() = 0;
	virtual void Kill(Entity*) = 0;
protected:
	int x, y;
	double speed, delay, time;
	short color;
	wchar_t symbol;
	bool isAlive;
protected:
	Direction eDirection;
	EntityType eEntityType;
};

#include "Bullet.h"
#include "Player.h"
#include "Cannon.h"
#include "Runner.h"
#include "Randomer.h"
#include "Chaser.h"


class Chaser : public Entity
{
public:

private:

};

class MovebleEntity : public Entity
{
public:

private:

};

class CheckPoint : public Entity
{
public:

private:

};

class Health : public Entity
{
public:

private:
};

class Ammo : public Entity
{
public:

private:

};
class Life : public Entity
{
public:

private:

};

#endif


