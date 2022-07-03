#include "Randomer.h"

Randomer::Randomer(int x, int y, short color, double speed) : Entity(x, y, color, Direction::Up, speed)
{
	eEntityType = EntityType::Randomer;
	pNumGenerator->SetRange((uint32_t)Direction::Up, (uint32_t)Direction::Right);
	symbol = '%';
	eDirection = (Direction)pNumGenerator->Randomize();
	//entitiesBuffer->SetEntity(x, y, this);
}

void Randomer::Update()
{
	for (int iTry = 0; iTry < 3; iTry++)			//�� ������, ���� �������� �������� ���-�� ���������
	{
		eDirection = (Direction)pNumGenerator->Randomize();
		int testX = x, testY = y;				//�������� ����������, ����� ��� ����, ����� ����� ������ �������� � ���� �����������

		switch (eDirection)
		{
			case Direction::Up:		testY--; break;
			case Direction::Down:	testY++; break;
			case Direction::Left:	testX--; break;
			case Direction::Right:	testX++; break;
		}

		wchar_t ch = pWindow->GetChar(testX, testY);

		//����� ����� ������ ��������� � ������� ������� ����
		if (ch == '\0' || ch == '#')	//����� �� ������� ������ ��� ������ � ������
			continue;
		else if (ch == ' ')				//������� - ����� �������� ���������� ���� � ��� �������
		{
			x = testX;
			y = testY;
			break;
		}
		else if (ch != ' ')				//���� �����-�� ������
		{
			Kill(GetEntity(testX, y));			//������� �������� � ���� �����������
			break;
		}
	}
}

void Randomer::Shoot()
{

}

void Randomer::Kill(Entity* target)
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