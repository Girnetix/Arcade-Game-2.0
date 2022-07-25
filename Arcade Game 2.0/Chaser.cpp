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
	double minDistanceToTarget = 0.0, distanceToTarget = 0.0;
	for (auto& currentPlayer : playerList)
	{
		distanceToTarget = sqrt((currentPlayer->GetX() - x) * (currentPlayer->GetX() - x) + (currentPlayer->GetY() - y) * (currentPlayer->GetY() - y));
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
