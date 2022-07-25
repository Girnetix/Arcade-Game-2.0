#include "Player.h"

int Player::idCounter = 0;
std::vector<Player*> playerList;

Player::Player(int x, int y, short color, Direction eDirection, double speed, const std::wstring& name) :Entity(x, y, color, eDirection, speed)
{
	symbol = (char)eDirection;
	eEntityType = EntityType::Player;
	this->name = name;
	id = idCounter++;					//����� ������ ������ ���������� �����
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
		//������� ����� ��������� � ���, ������� ������� �������� �� ����������� ������
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
	//��������� � ���, ��� ����� ���� (������ � ������� ����)
	Alive(false);
	std::wstring DeathMsg = L"";
	switch (killer->GetEntityType())
	{
		case EntityType::Bullet:								//��������� �����, ���� ������ ����� �� ����� ����� ������ ������ ��������, �� ����� ������ ��������� ����
		{
			Bullet* bullet = (Bullet*)killer;					//�.�. �� ����� �����, ��� ������ ���� ����� ������, ������ �������������� ����
			switch (bullet->GetOwner()->GetEntityType())		//�����, ��� ���������
			{
				case EntityType::Cannon: DeathMsg = L"����� ����� ������ " + this->name; break;
				case EntityType::Player:
				{
					Player* player = (Player*)bullet->GetOwner();
					DeathMsg = L"����� " + player->name + L" ���� ������ " + this->name; break;
				}
			}
		} break;
		case EntityType::Runner:   DeathMsg = L"����� ��������� ������ " + this->name;						break;
		case EntityType::Randomer: DeathMsg = L"�������� '��������' ���� ������ " + this->name;				break;
		case EntityType::Chaser:   DeathMsg = L"����� " + this->name + L" �� ����� ���������� �� ��������"; break;
		default:                   DeathMsg = L"����� " + this->name + L" ������ ���� �������";				break;
	}
}

void Player::PrintDeathMsg(const std::wstring& msg)
{

}