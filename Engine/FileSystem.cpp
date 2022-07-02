#include"FileSystem.h"

FileSystem* pFile = nullptr;

FileSystem::FileSystem()
{
	path = "";
	lastErr = L"";
}

FileSystem::~FileSystem()
{
	file.close();
}

void FileSystem::Create(const std::string& filename)
{
	if (file.is_open())							//���� � �������� ������� ���� �������� ����, �� ��������� ���
	{
		Save();
		file.open(filename, std::fstream::in);
		if (file.is_open())						//���� ���� � ��������� ��������� ��� ����������
		{
			Save();
			lastErr = L"���� � ����� ������ ��� ����������. ���������� ������ ��������.";
			return;
		}
		else
		{
			file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
			path = filename;
		}
	}
	else
	{
		file.open(filename, std::fstream::in);
		if (file.is_open())						//���� ���� � ��������� ��������� ��� ����������
		{
			Save();
			lastErr = L"���� � ����� ������ ��� ����������. ���������� ������ ��������.";
			return;
		}
		else
		{
			file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
			path = filename;
		}
	}
	lastErr = L"";
}

void FileSystem::Save()
{
	file.close();
	path = "";
}

void FileSystem::Load(const std::string& filename)
{
	if (file.is_open())							//���� � �������� ������� ���� �������� ����, �� ��������� ���
	{
		Save();
		file.open(filename, std::fstream::in);
		if (file.is_open())						//���� ���� � ��������� ��������� ������
		{
			Save();
			file.open(filename, std::fstream::in | std::fstream::out);
			path = filename;
		}
		else
		{
			file.close();
			lastErr = L"��������� ���� �� ������!";
			return;
		}
	}
	else
	{
		file.open(filename, std::fstream::in);
		if (file.is_open())						//���� ���� � ��������� ��������� ������
		{
			Save();
			file.open(filename, std::fstream::in | std::fstream::out);
			path = filename;
		}
		else
		{
			file.close();
			lastErr = L"��������� ���� �� ������!";
			return;
		}
	}
	lastErr = L"";
}

void FileSystem::Delete()
{
	file.close();
	remove(path.c_str());
	path = "";
}

std::wstring FileSystem::LastError()
{
	return lastErr;
}



