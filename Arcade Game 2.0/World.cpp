#include "World.h"

Entity* World::GetEntity(int x, int y)
{
	return entityBuffer[y * pWindow->GetScrWidth() + x].entity;
}

void World::SetEntity(int x, int y, Entity* entity)
{
	Entity* target = GetEntity(x, y);
	if (target != nullptr)
		CheckColission(entity, target);
	else
		entityBuffer[y * pWindow->GetScrWidth() + x].entity = entity;
}

void World::DeleteEntity(int x, int y)
{

}

void World::CheckColission(Entity* current, Entity* target)
{
	auto currentEntity = current->GetEntityType();
	auto targetEntity = target->GetEntityType();
	switch (current->GetEntityType())
	{
	case Entity::EntityType::Player:
		switch (targetEntity)
		{
		case Entity::EntityType::Player:
			break;
		case Entity::EntityType::Bullet:
			break;
		case Entity::EntityType::Cannon:
			break;
		case Entity::EntityType::Runner:
			break;
		case Entity::EntityType::Randomer:
			break;
		case Entity::EntityType::Chaser:
			break;
		case Entity::EntityType::MovableEntity:
			break;
		case Entity::EntityType::CheckPoint:
			break;
		case Entity::EntityType::Health:
			break;
		case Entity::EntityType::Ammo:
			break;
		case Entity::EntityType::Life:
			break;
		default:
			break;
		}
		break;
	case Entity::EntityType::Bullet:
		switch (targetEntity)
		{
		case Entity::EntityType::Player:
			break;
		case Entity::EntityType::Bullet:
			break;
		case Entity::EntityType::Cannon:
			break;
		case Entity::EntityType::Runner:
			break;
		case Entity::EntityType::Randomer:
			break;
		case Entity::EntityType::Chaser:
			break;
		case Entity::EntityType::MovableEntity:
			break;
		case Entity::EntityType::CheckPoint:
			break;
		case Entity::EntityType::Health:
			break;
		case Entity::EntityType::Ammo:
			break;
		case Entity::EntityType::Life:
			break;
		default:
			break;
		}
		break;
	case Entity::EntityType::Runner:
		switch (targetEntity)
		{
		case Entity::EntityType::Player:
			break;
		case Entity::EntityType::Bullet:
			break;
		case Entity::EntityType::Cannon:
			break;
		case Entity::EntityType::Runner:
			break;
		case Entity::EntityType::Randomer:
			break;
		case Entity::EntityType::Chaser:
			break;
		case Entity::EntityType::MovableEntity:
			break;
		case Entity::EntityType::CheckPoint:
			break;
		case Entity::EntityType::Health:
			break;
		case Entity::EntityType::Ammo:
			break;
		case Entity::EntityType::Life:
			break;
		default:
			break;
		}
		break;
	case Entity::EntityType::Randomer:
		switch (targetEntity)
		{
		case Entity::EntityType::Player:
			break;
		case Entity::EntityType::Bullet:
			break;
		case Entity::EntityType::Cannon:
			break;
		case Entity::EntityType::Runner:
			break;
		case Entity::EntityType::Randomer:
			break;
		case Entity::EntityType::Chaser:
			break;
		case Entity::EntityType::MovableEntity:
			break;
		case Entity::EntityType::CheckPoint:
			break;
		case Entity::EntityType::Health:
			break;
		case Entity::EntityType::Ammo:
			break;
		case Entity::EntityType::Life:
			break;
		default:
			break;
		}
		break;
	case Entity::EntityType::Chaser:
		switch (targetEntity)
		{
		case Entity::EntityType::Player:
			break;
		case Entity::EntityType::Bullet:
			break;
		case Entity::EntityType::Cannon:
			break;
		case Entity::EntityType::Runner:
			break;
		case Entity::EntityType::Randomer:
			break;
		case Entity::EntityType::Chaser:
			break;
		case Entity::EntityType::MovableEntity:
			break;
		case Entity::EntityType::CheckPoint:
			break;
		case Entity::EntityType::Health:
			break;
		case Entity::EntityType::Ammo:
			break;
		case Entity::EntityType::Life:
			break;
		default:
			break;
		}
		break;
	default:
		break;
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
	SetEntity(entity->GetX(), entity->GetY(), entity);
}

void World::UpdateWorld(double deltaTime)
{

}
