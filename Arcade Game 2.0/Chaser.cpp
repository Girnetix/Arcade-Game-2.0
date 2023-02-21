#include "Chaser.h"

Chaser::Chaser(int x, int y, short color, Direction eDirection, double speed) :Entity(x, y, color, eDirection, speed)
{
	eEntityType = EntityType::Chaser;
	symbol = '&';
	pWindow->PrintSymbol(x, y, symbol, color);
	CreateEntity(this);
}

void Chaser::Update()
{
	targetPlayer = FindPlayer();
	color = targetPlayer->GetEntityColor();
	int testX = x, testY = y;

}

void Chaser::OnCollisionEntity(Entity* target)
{

}

Entity* Chaser::FindPlayer()
{
	Player* closerPlayer = nullptr;
	int dx = 0, dy = 0;
	double minDistanceToTarget = 0.0, distanceToTarget = 0.0;
	for (auto& currentPlayer : playerList)
	{
		dx = currentPlayer->GetX() - x;
		dy = currentPlayer->GetY() - y;
		distanceToTarget = sqrt(dx * dx + dy * dy);
		if (minDistanceToTarget == 0.0)
		{
			minDistanceToTarget = distanceToTarget;
			closerPlayer = currentPlayer;
		}
		else if (distanceToTarget < minDistanceToTarget)
		{
			minDistanceToTarget = distanceToTarget;
			closerPlayer = currentPlayer;
		}
	}
	if (minDistanceToTarget < maxDistance)
		return closerPlayer;
	else
		return nullptr;
}
