#include "Entity.h"

Entity::Entity()
{
	x = y = color = 0;
	eDirection = Direction::Up;
	eEntityType = EntityType::Player;
	speed = delay = time = 0.0;
	symbol = ' ';
	isAlive = true;
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

void Entity::DestroyEntity(Entity* entity)
{
	/*for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
		if (*it == entity)
		{
			entities.erase(it);
			break;
		}*/
}

int Entity::GetX()
{
	return x;
}

int Entity::GetY()
{
	return y;
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

		
		pWindow->ClearSymbol(x, y, symbol);

		Update();
		if (IsAlive())
		{

			pWindow->PrintSymbol(x, y, symbol, color);
		}
		else
		{
			if (eEntityType != EntityType::Player)
				DestroyEntity(this);
		}
	}
}

Entity* Entity::GetEntity(int x, int y)
{
	//поиск сущности по полученным координатам
	return nullptr;
}

Entity::EntityType Entity::GetEntityType()
{
	return eEntityType;
}

Entity::Direction Entity::GetDiretion()
{
	return eDirection;
}

