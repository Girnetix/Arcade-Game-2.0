#include "Cannon.h"

Cannon::Cannon(int x, int y, short color, Direction eDirection, double speed) :Entity(x, y, color, eDirection, speed)
{
	eEntityType = EntityType::Cannon;
	switch (eDirection)
	{
		case Direction::Up:		symbol = '|'; break;
		case Direction::Down:	symbol = '|'; break;
		case Direction::Left:	symbol = '-'; break;
		case Direction::Right:	symbol = '-'; break;
	}
	//entitiesBuffer->SetEntity(x, y, this);
	pWindow->PrintSymbol(x, y, symbol, color);
}

void Cannon::Update()
{
	Shoot();
}

void Cannon::Shoot()
{
	//entities.push_back(new Bullet(x, y, FG_RED | BG_BLACK, eDirection, this, 50.0));
}

void Cannon::Kill(Entity* killer)
{

}