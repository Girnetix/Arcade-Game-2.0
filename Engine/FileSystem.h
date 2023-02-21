#pragma once
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <fstream>
#include <cstdio>

class File
{
public:
	File();
	~File();
	void Create(const std::string& filename);
	void Save();
	void Load(const std::string& filename);
	int Rename(const std::string& oldName, const std::string newName);
	void Delete();
	template<typename Type>
	File& operator <<(const Type& data)
	{
		file << data;
		return *this;
	}
	template<typename Type>
	File& operator >>(Type& data)
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
	bool IsOpen()
	{
		return file.is_open();
	}
private:
	std::fstream file;
	std::string path, lastErr;
};

#endif