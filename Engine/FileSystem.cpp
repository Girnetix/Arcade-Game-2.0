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
	if (file.is_open())							//если у текущего объекта есть открытый файл, то сохраняем его
	{
		Save();
		file.open(filename, std::fstream::in);
		if (file.is_open())						//если файл с указанным названием уже существует
		{
			Save();
			lastErr = L"Файл с таким именем уже существует. Придумайте другое название.";
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
		if (file.is_open())						//если файл с указанным названием уже существует
		{
			Save();
			lastErr = L"Файл с таким именем уже существует. Придумайте другое название.";
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
	if (file.is_open())							//если у текущего объекта есть открытый файл, то сохраняем его
	{
		Save();
		file.open(filename, std::fstream::in);
		if (file.is_open())						//если файл с указанным названием найден
		{
			Save();
			file.open(filename, std::fstream::in | std::fstream::out);
			path = filename;
		}
		else
		{
			file.close();
			lastErr = L"Указанный файл не найден!";
			return;
		}
	}
	else
	{
		file.open(filename, std::fstream::in);
		if (file.is_open())						//если файл с указанным названием найден
		{
			Save();
			file.open(filename, std::fstream::in | std::fstream::out);
			path = filename;
		}
		else
		{
			file.close();
			lastErr = L"Указанный файл не найден!";
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



