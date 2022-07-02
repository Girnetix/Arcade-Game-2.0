#include "Player.h"

int Player::idCounter = 0;
int Player::X = 0;
int Player::Y = 5;

Player::Player(int x, int y, short color, Direction eDirection, double speed, const std::wstring& name) :Entity(x, y, color, eDirection, speed)
{
	symbol = (char)eDirection;
	eEntityType = EntityType::Player;
	this->name = name;
	id = idCounter++;					//задаём нашему игроку уникальный номер
	entitiesBuffer->SetEntity(x, y, this);
}

void Player::Update()
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

void Player::Shoot()
{
	if (countOfBullets)
	{
		countOfBullets--;
		entities.push_back(new Bullet(x, y, FG_BLUE | BG_BLACK, eDirection, this, 50.0));
	}
}

void Player::Kill(Entity* killer)
{
	//сообщение о том, что игрок умер (только в сетевой игре) !ДОБАВИТЬ ПРОВЕРКУ!
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
	PrintDeathMsg(DeathMsg);
}

void Player::PrintDeathMsg(const std::wstring& msg)
{

}