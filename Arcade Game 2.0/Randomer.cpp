#include "Randomer.h"

Randomer::Randomer(int x, int y, int minX, int minY, int maxX, int maxY, short color, double speed) : Entity(x, y, color, Direction::Up, speed)
{
	eEntityType = EntityType::Randomer;
	pNumGenerator->SetRange((uint32_t)Direction::Up, (uint32_t)Direction::Right);
	symbol = '%';
	eDirection = (Direction)pNumGenerator->Randomize();
	pWindow->PrintSymbol(x, y, symbol, color);
	CreateEntity(this);
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
}

void Randomer::OnCollisionEntity(Entity* target)
{
	switch (target->GetEntityType())
	{
	case Entity::EntityType::Player:
	{
		Player* player = (Player*)target;
		player->Kill(this);
		Alive(false);
		break;
	}
	case Entity::EntityType::Bullet:
	{
		target->Alive(false);
		Alive(false);
		break;
	}
	default:
		break;
	}
}

void Randomer::Update()
{
	int failedAttempts = 0;
	bool moveIsLegal = false;
	while (!moveIsLegal || failedAttempts != 10)						//на случай, если рандомер случайно где-то застр€нет
	{
		eDirection = (Direction)pNumGenerator->Randomize();
		int testX = x, testY = y;				//тестовые координаты, нужны дл€ того, чтобы проверить будущую позицию на наличие или отсутсвие объектов

		DeleteEntityFromBuf(this);
		pWindow->ClearSymbol(x, y, symbol);

		switch (eDirection)
		{
			case Direction::Up:
			{
				if (testY > minY)
				{
					testY--;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}
			case Direction::Down: 
			{
				if (testY < maxY)
				{
					testY++;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}	
			case Direction::Left:
			{
				if (testX > minX)
				{
					testX--;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}
			case Direction::Right:
			{
				if (testX < maxX)
				{
					testX++;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}
		}

		if (moveIsLegal)
		{
			wchar_t ch = pWindow->GetChar(testX, testY);

			//узнаЄм какой символ находитс€ в будущей позиции рандомера
			if (ch == '\0' || ch == '#')	//вышли за пределы экрана или попали в стенку
			{
				moveIsLegal = false;
				failedAttempts++;
				continue;
			}		
			else if (ch != ' ')				//есть какой-то символ
			{
				SetEntityToBuf(this);
				break;
			}
			else if (ch == ' ')				//пустота - можно спокойно перемещать рандомера в эту позицию
			{
				x = testX;
				y = testY;
				SetEntityToBuf(this);
				pWindow->PrintSymbol(x, y, symbol, color);
				break;
			}
		}
		else
			continue;
	}
}