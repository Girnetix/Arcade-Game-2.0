#include "Bullet.h"

Bullet::Bullet(int x, int y, short color, Direction eDirection, Entity* owner, double speed) :Entity(x, y, color, eDirection, speed)
{
	switch (eDirection)
	{
		case Direction::Up:    this->y--;		break;
		case Direction::Down:  this->y++;		break;
		case Direction::Left:  this->x--;		break;
		case Direction::Right: this->x++;		break;
	}
	entitiesBuffer->SetEntity(x, y, this);
	this->owner = owner;
	symbol = 'O';
	eEntityType = EntityType::Bullet;

	wchar_t ch = pWindow->GetChar(this->x, this->y);

	//узнаём какой символ находится в будущей позиции пули
	if (ch == '\0' || ch == '#')//вышли за пределы экрана или попали в стенку
		Alive(false);
	else if (ch == ' ')			//пустота - можно спокойно перемещать пулю в эту позицию
		pWindow->PrintSymbol(this->x, this->y, symbol, color);
	else if (ch != ' ')				//есть какой-то символ
	{
		Entity* currentEntity = GetEntity(this->x, this->y);		//ищем сущность, которая находится в этой позиции
		if (currentEntity != nullptr)						//если сущность найдена - убиваем её
			Kill(currentEntity);
	}
}

Entity* Bullet::GetOwner()
{
	return owner;
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

	wchar_t ch = pWindow->GetChar(testX, testY);

	//узнаём какой символ находится в будущей позиции пули
	if (ch == '\0' || ch == '#')//вышли за пределы экрана или попали в стенку
		Alive(false);
	else if (ch == ' ')			//пустота - можно спокойно перемещать пулю в эту позицию
	{
		x = testX;
		y = testY;
	}
	else if (ch != ' ')				//есть какой-то символ
		Kill(GetEntity(testX, y));			//убиваем сущность в этих координатах
}

void Bullet::Shoot()
{
}

void Bullet::Kill(Entity* target)
{
	switch (target->GetEntityType())
	{
		case EntityType::Player:
		{
			Player* player = (Player*)target;
			player->Kill(this);
			Alive(false);
			break;
		}
		case EntityType::Chaser: break;
		case EntityType::Randomer: break;
		case EntityType::Runner: break;
		case EntityType::Bullet: break;
		default: break;
	}
}