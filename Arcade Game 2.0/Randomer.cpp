#include "Randomer.h"

Randomer::Randomer(int x, int y, int minX, int minY, int maxX, int maxY, short color, double speed) : Entity(x, y, color, Direction::Up, speed)
{
	eEntityType = EntityType::Randomer;
	pNumGenerator->SetRange((uint32_t)Direction::Up, (uint32_t)Direction::Right);
	symbol = '%';
	eDirection = (Direction)pNumGenerator->Randomize();
	pWindow->PrintSymbol(x, y, symbol, color);
	CreateEntity(this);
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
}

void Randomer::OnCollisionEntity(Entity* target)
{
	switch (target->GetEntityType())
	{
	case Entity::EntityType::Player:
	{
		Player* player = (Player*)target;
		player->Kill(this);
		Alive(false);
		break;
	}
	case Entity::EntityType::Bullet:
	{
		target->Alive(false);
		Alive(false);
		break;
	}
	default:
		break;
	}
}

void Randomer::Update()
{
	int failedAttempts = 0;
	bool moveIsLegal = false;
	while (!moveIsLegal || failedAttempts != 10)						//�� ������, ���� �������� �������� ���-�� ���������
	{
		eDirection = (Direction)pNumGenerator->Randomize();
		int testX = x, testY = y;				//�������� ����������, ����� ��� ����, ����� ��������� ������� ������� �� ������� ��� ��������� ��������

		DeleteEntityFromBuf(this);
		pWindow->ClearSymbol(x, y, symbol);

		switch (eDirection)
		{
			case Direction::Up:
			{
				if (testY > minY)
				{
					testY--;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}
			case Direction::Down: 
			{
				if (testY < maxY)
				{
					testY++;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}	
			case Direction::Left:
			{
				if (testX > minX)
				{
					testX--;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}
			case Direction::Right:
			{
				if (testX < maxX)
				{
					testX++;
					moveIsLegal = true;
				}
				else
					failedAttempts++;
				break;
			}
		}

		if (moveIsLegal)
		{
			wchar_t ch = pWindow->GetChar(testX, testY);

			//����� ����� ������ ��������� � ������� ������� ���������
			if (ch == '\0' || ch == '#')	//����� �� ������� ������ ��� ������ � ������
			{
				moveIsLegal = false;
				failedAttempts++;
				continue;
			}		
			else if (ch != ' ')				//���� �����-�� ������
			{
				SetEntityToBuf(this);
				break;
			}
			else if (ch == ' ')				//������� - ����� �������� ���������� ��������� � ��� �������
			{
				x = testX;
				y = testY;
				SetEntityToBuf(this);
				pWindow->PrintSymbol(x, y, symbol, color);
				break;
			}
		}
		else
			continue;
	}
}