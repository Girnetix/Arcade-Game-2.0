#pragma once
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <fstream>
#include <cstdio>

class FileSystem
{
public:
	FileSystem();
	~FileSystem();
	void Create(const std::string& filename);
	void Save();
	void Load(const std::string& filename);
	void Delete();
	std::wstring LastError();
	template<typename Type>
	FileSystem& operator <<(const Type& data)
	{
		file << data;
		return *this;
	}
	template<typename Type>
	FileSystem& operator >>(Type& data)
	{
		file >> data;
		return *this;
	}
	template<typename Type>
	void Write(const Type& data)
	{
		file.write((const char*)&data, sizeof(data));
	}
	template<typename Type>
	void Read(Type& data)
	{
		file.read((char*)&data, sizeof(data));
	}
	bool EndOfFile()
	{
		return file.eof();
	}
private:
	std::fstream file;
	std::string path;
	std::wstring lastErr;
};

extern FileSystem* pFile;

#endif