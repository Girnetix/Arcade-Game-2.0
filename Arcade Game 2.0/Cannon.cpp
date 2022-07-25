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
	CreateEntity(this);
}

void Cannon::OnCollisionEntity(Entity* target)
{
}

void Cannon::Update()
{
	Shoot();
}

void Cannon::Shoot()
{
	CreateEntity(new Bullet(x, y, FG_RED | BG_BLACK, eDirection, this, 50.0));
}
