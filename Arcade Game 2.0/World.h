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
	void SetEntity(int x, int y, Entity* entity);
	void DeleteEntity(int x, int y);
	void CheckColission(Entity* currentEntity, Entity* targetEntity);
public:
	World();
	~World();
	void CreateEntity(Entity* entity);
	void UpdateWorld(double deltaTime);
private:
	std::vector<Entity*> entities;
	EntityBuffer* entityBuffer = nullptr;
};

#endif
