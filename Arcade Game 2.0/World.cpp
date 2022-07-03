#include "World.h"

Entity* World::GetEntity(int x, int y)
{
	return entityBuffer[y * pWindow->GetScrWidth() + x].entity;
}

void World::SetEntityToBuf(int x, int y, Entity* entity)
{
	Entity* target = GetEntity(x, y);
	if (target != nullptr)
		entity->OnCollisionEntity(target);
	else
		entityBuffer[y * pWindow->GetScrWidth() + x].entity = entity;
}

void World::DeleteEntityFromBuf(int x, int y)
{
	entityBuffer[y * pWindow->GetScrWidth() + x].entity = nullptr;
}

void World::DestroyEntity(Entity* entity)
{
	int x = entity->GetX(), y = entity->GetY();
	Entity* target = GetEntity(x, y);
	if (target != nullptr)
	{
		DeleteEntityFromBuf(x, y);
		for (auto iter = entities.begin(); iter != entities.end(); iter++)
			if (*iter == target)
			{
				entities.erase(iter);
				break;
			}
	}
}

World::World()
{
	int size = pWindow->GetScrWidth() * pWindow->GetScrHeight();
	entityBuffer = new EntityBuffer[size];
}

World::~World()
{
	delete[] entityBuffer;
}

void World::CreateEntity(Entity* entity)
{
	entities.push_back(entity);
	SetEntityToBuf(entity->GetX(), entity->GetY(), entity);
}

void World::UpdateWorld(double deltaTime)
{
	for (auto iter = entities.begin(); iter != entities.end();)
	{
		Entity* currentEntity = *iter;
		DeleteEntityFromBuf(currentEntity->GetX(), currentEntity->GetY());
		currentEntity->UpdateEntity(deltaTime);
		if (currentEntity->IsAlive())
		{
			SetEntityToBuf(currentEntity->GetX(), currentEntity->GetY(), currentEntity);
			iter++;
		}
		else
			if (currentEntity->GetEntityType() != Entity::EntityType::Player)
				iter = entities.erase(iter);
	}
}
