#include "Player.h"

int Player::idCounter = 0;
int Player::X = 0;
int Player::Y = 5;

Player::Player(int x, int y, short color, Direction eDirection, double speed, const std::wstring& name) :Entity(x, y, color, eDirection, speed)
{
	symbol = (char)eDirection;
	eEntityType = EntityType::Player;
	this->name = name;
	id = idCounter++;					//����� ������ ������ ���������� �����
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
	//��������� � ���, ��� ����� ���� (������ � ������� ����) !�������� ��������!
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
	PrintDeathMsg(DeathMsg);
}

void Player::PrintDeathMsg(const std::wstring& msg)
{

}