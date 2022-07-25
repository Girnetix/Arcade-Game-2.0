#include "Player.h"

int Player::idCounter = 0;
std::vector<Player*> playerList;

Player::Player(int x, int y, short color, Direction eDirection, double speed, const std::wstring& name) :Entity(x, y, color, eDirection, speed)
{
	symbol = (char)eDirection;
	eEntityType = EntityType::Player;
	this->name = name;
	id = idCounter++;					//задаём нашему игроку уникальный номер
	CreateEntity(this);
	playerList.push_back(this);
}

void Player::Update()
{
	if (IsAlive())
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			Shoot();
		switch (eDirection)
		{
			case Direction::Up:		symbol = (char)24; break;
			case Direction::Down:	symbol = (char)25; break;
			case Direction::Left:	symbol = (char)27; break;
			case Direction::Right:	symbol = (char)26; break;
		}
	}
	else
	{
		timeForRespawning -= pTimer->GetDeltaTimeSec();
		//сделать вывод сообщения о том, сколько времени осталось до возрождения игрока
		if (timeForRespawning <= 0.0)
		{
			Alive(true);
			timeForRespawning = timeRespawn;
		}
	}
}

void Player::OnCollisionEntity(Entity* target)
{

}

void Player::Shoot()
{
	if (countOfBullets)
	{
		countOfBullets--;
		CreateEntity(new Bullet(x, y, FG_BLUE | BG_BLACK, eDirection, this, 50.0));
	}
}

void Player::Kill(Entity* killer)
{
	//сообщение о том, что игрок умер (только в сетевой игре)
	Alive(false);
	std::wstring DeathMsg = L"";
	switch (killer->GetEntityType())
	{
		case EntityType::Bullet:								//поскольку пушка, либо другой игрок не может убить нашего игрока напрямую, то нужно узнать владельца пули
		{
			Bullet* bullet = (Bullet*)killer;					//т.к. мы точно знаем, что именно пуля убила игрока, делаем преобразование типа
			switch (bullet->GetOwner()->GetEntityType())		//узнаём, кто выстрелил
			{
				case EntityType::Cannon: DeathMsg = L"Пушка убила игрока " + this->name; break;
				case EntityType::Player:
				{
					Player* player = (Player*)bullet->GetOwner();
					DeathMsg = L"Игрок " + player->name + L" убил игрока " + this->name; break;
				}
			}
		} break;
		case EntityType::Runner:   DeathMsg = L"Бегун перебежал игрока " + this->name;						break;
		case EntityType::Randomer: DeathMsg = L"Рандомер 'случайно' убил игрока " + this->name;				break;
		case EntityType::Chaser:   DeathMsg = L"Игрок " + this->name + L" не успел спрятаться от охотника"; break;
		default:                   DeathMsg = L"Игрок " + this->name + L" открыл ящик Пандоры";				break;
	}
}

void Player::PrintDeathMsg(const std::wstring& msg)
{

}