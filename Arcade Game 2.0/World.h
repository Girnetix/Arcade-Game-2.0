#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include <Engine/Engine.h>

class World
{
private:
	class EntityBuffer
	{
	public:
		Entity* entity = nullptr;
	};
private:
	Entity* GetEntity(int x, int y);
public:
	World();
	~World();
	void CreateEntity(Entity* entity);
	void UpdateWorld(double deltaTime);

	void DestroyEntity(Entity* entity);
	void SetEntityToBuf(int x, int y, Entity* entity);
	void DeleteEntityFromBuf(int x, int y);
private:
	std::vector<Entity*> entities;
	EntityBuffer* entityBuffer = nullptr;
};

#endif
