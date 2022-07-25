#include "World.h"
#include "Entity.h"

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
	entity->SetWorld(this);
	entities.push_back(entity);
	SetEntityToBuf(entity->GetX(), entity->GetY(), entity);
}

void World::UpdateWorld(double deltaTime)
{
	for (auto iter = entities.begin(); iter != entities.end();)
	{
		Entity* currentEntity = *iter;
		if (currentEntity->IsAlive())
		{
			currentEntity->UpdateEntity(deltaTime);
			iter++;
		}
		else
			if (currentEntity->GetEntityType() != Entity::EntityType::Player)
				iter = entities.erase(iter);
			else
				currentEntity->UpdateEntity(deltaTime);
	}
}
