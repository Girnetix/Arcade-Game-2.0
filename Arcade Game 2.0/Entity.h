#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <Engine/Engine.h>
#include <vector>

class World;

class Entity
{
public:
	enum class Direction { Up = 24, Down, Left, Right };
	enum class EntityType{ Player, Bullet, Cannon, Runner, Randomer, Chaser, MovableEntity, CheckPoint, Health, Ammo, Life };
public:
	Entity();
	Entity(int x, int y, short color, Direction eDirection, double speed);

	void CreateEntity(Entity* entity);
	void SetEntityToBuf(Entity* entity);
	void DeleteEntityFromBuf(Entity* entity);

	int GetX();
	int GetY();

	short GetEntityColor();
	wchar_t GetEntitySymbol();

	void Alive(bool isAlive);
	bool IsAlive();

	void UpdateEntity(double deltaTime);

	Entity* GetEntity(int x, int y);

	EntityType GetEntityType();
	Direction GetDiretion();

	void SetWorld(World* world);
	World* GetWorld();
public:
	virtual void OnCollisionEntity(Entity* target) = 0;
protected:
	virtual void Update() = 0;
protected:
	int x, y;
	double speed, delay, time;
	short color;
	wchar_t symbol;
	bool isAlive;
	World* world;
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


