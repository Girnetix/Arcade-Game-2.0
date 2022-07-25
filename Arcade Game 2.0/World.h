#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <Engine/Engine.h>

class Entity;

class World
{
private:
	class EntityBuffer
	{
	public:
		Entity* entity = nullptr;
	};
public:
	World();
	~World();
	void CreateEntity(Entity* entity);
	void UpdateWorld(double deltaTime);

	void SaveWorld(std::wstring filename);
	void LoadWorld(std::wstring filename);

	void SetEntityToBuf(int x, int y, Entity* entity);
	void DeleteEntityFromBuf(int x, int y);

	Entity* GetEntity(int x, int y);
private:
	std::vector<Entity*> entities;
	EntityBuffer* entityBuffer = nullptr;
};

#endif
