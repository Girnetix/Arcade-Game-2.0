#include "Entity.h"
#include "World.h"

Entity::Entity()
{
	x = y = color = 0;
	eDirection = Direction::Up;
	eEntityType = EntityType::Player;
	speed = delay = time = 0.0;
	symbol = ' ';
	isAlive = true;
	world = nullptr;
}

Entity::Entity(int x, int y, short color, Direction eDirection, double speed) :Entity()
{
	this->x = x;
	this->y = y;
	this->color = color;
	this->eDirection = eDirection;
	this->speed = speed;
	if (speed > 0)
		delay = 1.0 / speed;				//количество действий за секунду
	else
		delay = 0.0;
}

void Entity::CreateEntity(Entity* entity)
{
	pWorld->CreateEntity(entity);
}

void Entity::SetEntityToBuf(Entity* entity)
{
	pWorld->SetEntityToBuf(entity->x, entity->y, entity);
}

void Entity::DeleteEntityFromBuf(Entity* entity)
{
	pWorld->DeleteEntityFromBuf(entity->x, entity->y);
}

int Entity::GetX()
{
	return x;
}

int Entity::GetY()
{
	return y;
}

short Entity::GetEntityColor()
{
	return color;
}

wchar_t Entity::GetEntitySymbol()
{
	return symbol;
}

void Entity::Alive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool Entity::IsAlive()
{
	return isAlive;
}

void Entity::UpdateEntity(double deltaTime)
{
	time += deltaTime;
	if (time >= delay)
	{
		time -= delay;
		Update();
	}
}

Entity* Entity::GetEntity(int x, int y)
{
	return pWorld->GetEntity(x, y);
}

Entity::EntityType Entity::GetEntityType()
{
	return eEntityType;
}

Entity::Direction Entity::GetDiretion()
{
	return eDirection;
}

void Entity::SetWorld(World* world)
{
	this->world = world;
}

World* Entity::GetWorld()
{
	return pWorld;
}

