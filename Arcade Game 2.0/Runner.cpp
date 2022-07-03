#include "Runner.h"

Runner::Runner(int x, int y, short color, Direction eDirection, double speed) : Entity(x, y, color, eDirection, speed)
{
	eEntityType = EntityType::Runner;
	eDirection = Direction::Left;
	symbol = 'S';
	pWindow->PrintSymbol(x, y, symbol, FG_GREEN | BG_BLACK);
	//entitiesBuffer->SetEntity(x, y, this);
}

void Runner::Update()
{
	int testX = x;
	switch (eDirection)
	{
		case Direction::Left:  testX--; break;
		case Direction::Right: testX++; break;
	}

	wchar_t ch = pWindow->GetChar(testX, y);

	if (ch == ' ')
		x = testX;
	else if (ch == '#' || ch == '\0')
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
	}
	else
		Kill(GetEntity(testX, y));
}

void Runner::Shoot()
{

}

void Runner::Kill(Entity* target)
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