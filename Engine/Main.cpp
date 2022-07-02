#include "Engine.h"
class Point
{
public:

	Point()
	{
		x = y = z = 0;
	}
	Point(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void Create(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	wstring Print()
	{
		return L"x = " + to_wstring(x) + L" y = " + to_wstring(y) + L" z = " + to_wstring(z);
	}
private:
	int x, y, z;
};
int main()
{
	Window window;
	window.ConstructWindow(120, 50, L"Тест");
	FileSystem file;
	Point p[25];
	int i = 1;
	file.Load("test.txt");
	for (int i = 0; i < 25; i++)
	{
		p[i].Create(i, i, i);
		file.Write(p[i]);
	}
	//for (int i = 0; i < 25; i++)
	//{
	//	file.Read(p[i]);
	//	window.PrintMsg(0, i + 1, p[i].Print());
	//}
	//file.Delete();
	file.Save();
	window.UpdateWindow();
	return 0;
}