#include "Runner.h"

Runner::Runner(int x, int y, short color, Direction eDirection, double speed) : Entity(x, y, color, eDirection, speed)
{
	eEntityType = EntityType::Runner;
	this->eDirection = Direction::Left;
	symbol = 'S';
	pWindow->PrintSymbol(x, y, symbol, FG_GREEN | BG_BLACK);
	CreateEntity(this);
}

void Runner::OnCollisionEntity(Entity* target)
{
	switch (target->GetEntityType())
	{
		case Entity::EntityType::Player:
		{
			Player* player = (Player*)target;
			player->Kill(this);
			break;
		}
		case Entity::EntityType::Bullet:
		{
			Alive(false);
			target->Alive(false);
			break;
		}
		default: 
		{
			pWindow->PrintSymbol(x, y, symbol, color);
			SetEntityToBuf(this); 
			break;
		}
	}
}

void Runner::Update()
{
	int testX = x;

	switch (eDirection)
	{
		case Direction::Left:  testX--; break;
		case Direction::Right: testX++; break;
	}

	pWindow->ClearSymbol(x, y, symbol);
	DeleteEntityFromBuf(this);
	wchar_t ch = pWindow->GetChar(testX, y);

	if (ch == '#' || ch == '\0')
	{
		switch (eDirection)
		{
			case Direction::Left:
			{
				eDirection = Direction::Right;
				x++;
				break;
			}
			case Direction::Right:
			{
				eDirection = Direction::Left;
				x--;
				break;
			}
		}
		pWindow->PrintSymbol(x, y, symbol, color);
		SetEntityToBuf(this);
	}
	else if (ch != ' ')	
		SetEntityToBuf(this);
	else
	{
		x = testX;
		pWindow->PrintSymbol(x, y, symbol, color);
		SetEntityToBuf(this);
	}
}
