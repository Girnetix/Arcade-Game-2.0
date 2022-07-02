#include "Input.h"

bool Keyboard::KeyIsPressed(int numKey)
{
	return GetAsyncKeyState(numKey);
}
