#include "FileSystem.h"

File::File()
{
	file.exceptions(std::fstream::failbit | std::fstream::badbit);
	lastErr = path = "";
}

File::~File()
{
	file.close();
	lastErr = path = "";
}

void File::Create(const std::string& filename)
{
	if (!IsOpen())
	{
		try
		{
			file.open(filename, std::fstream::out);
			file.close();
			Load(filename);
		}
		catch (const std::exception& ex)
		{
			lastErr = ex.what();
		}
	}
	else
		throw "Use another file object to open the file!";
}

void File::Save()
{
	if (file.is_open())
		file.close();
	path = "";
}

void File::Load(const std::string& filename)
{
	if (!IsOpen())
	{
		try
		{
			file.open(filename, std::fstream::out | std::fstream::in);
			path = filename;
		}
		catch (const std::exception& ex)
		{
			lastErr = ex.what();
			Create(filename);
		}
	}
	else
		throw "Use another file object to open the file!";
}

int File::Rename(const std::string& oldName, const std::string newName)
{
	Save();
	int result = rename(oldName.c_str(), newName.c_str());
	if (result == 0)
		path = newName;
	return result;
}

void File::Delete()
{
	Save();
	remove(path.c_str());
}





