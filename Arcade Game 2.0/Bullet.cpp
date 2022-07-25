#include "Bullet.h"

Bullet::Bullet(int x, int y, short color, Direction eDirection, Entity* owner, double speed) :Entity(x, y, color, eDirection, speed)
{
	int testX = x, testY = y;
	switch (eDirection)
	{
		case Direction::Up:    testY--;		break;
		case Direction::Down:  testY++;		break;
		case Direction::Left:  testX--;		break;
		case Direction::Right: testX++;		break;
	}

	this->owner = owner;
	symbol = 'O';
	eEntityType = EntityType::Bullet;

	wchar_t ch = pWindow->GetChar(testX, testY);

	//узнаём какой символ находится в будущей позиции пули
	if (ch == '\0' || ch == '#')	//вышли за пределы экрана или попали в стенку
	{
		CreateEntity(this);
		Alive(false);
	}
	else if (ch != ' ')			//есть какой-то объект
		CreateEntity(this);
	else
	{
		this->x = testX;
		this->y = testY;
		CreateEntity(this);
		pWindow->PrintSymbol(this->x, this->y, this->symbol, this->color);
	}	
}

Entity* Bullet::GetOwner()
{
	return owner;
}

void Bullet::OnCollisionEntity(Entity* target)
{
	switch (target->GetEntityType())
	{
		case Entity::EntityType::Player:
		{
			Player* player = (Player*)target;
			player->Kill(this);
			Alive(false);
		}
			break;
		case Entity::EntityType::Runner:
			break;
		case Entity::EntityType::Randomer:
			break;
		case Entity::EntityType::Chaser:
			break;
		case Entity::EntityType::Bullet:	pWindow->PrintSymbol(x, y, symbol, color);	break;
		default: Alive(false); break;
	}
}

void Bullet::Update()
{
	int testX = x, testY = y;				//тестовые координаты, нужны для того, чтобы найти другую сущность в этих координатах

	switch (eDirection)
	{
		case Direction::Up:		testY--; break;
		case Direction::Down:	testY++; break;
		case Direction::Left:	testX--; break;
		case Direction::Right:	testX++; break;
	}

	DeleteEntityFromBuf(this);
	pWindow->ClearSymbol(x, y, symbol);
	wchar_t ch = pWindow->GetChar(testX, testY);

	//узнаём какой символ находится в будущей позиции пули
	if (ch == '\0' || ch == '#')	//вышли за пределы экрана или попали в стенку
		Alive(false);
	else if (ch != ' ')
	{
		x = testX;
		y = testY;
		SetEntityToBuf(this);
	}
	else
	{
		x = testX;
		y = testY;
		SetEntityToBuf(this);
		pWindow->PrintSymbol(x, y, symbol, color);
	}
}

