#include "Randomer.h"

Randomer::Randomer(int x, int y, short color, double speed) : Entity(x, y, color, Direction::Up, speed)
{
	eEntityType = EntityType::Randomer;
	pNumGenerator->SetRange((uint32_t)Direction::Up, (uint32_t)Direction::Right);
	symbol = '%';
	eDirection = (Direction)pNumGenerator->Randomize();
	//entitiesBuffer->SetEntity(x, y, this);
}

void Randomer::Update()
{
	for (int iTry = 0; iTry < 3; iTry++)			//на случай, если рандомер случайно где-то застрянет
	{
		eDirection = (Direction)pNumGenerator->Randomize();
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
		if (ch == '\0' || ch == '#')	//вышли за пределы экрана или попали в стенку
			continue;
		else if (ch == ' ')				//пустота - можно спокойно перемещать пулю в эту позицию
		{
			x = testX;
			y = testY;
			break;
		}
		else if (ch != ' ')				//есть какой-то символ
		{
			Kill(GetEntity(testX, y));			//убиваем сущность в этих координатах
			break;
		}
	}
}

void Randomer::Shoot()
{

}

void Randomer::Kill(Entity* target)
{
	switch (target->GetEntityType())
	{
		case EntityType::Player:
		{
			Player* player = (Player*)target;
			player->Kill(this);
			break;
		}
		default: break;
	}
}