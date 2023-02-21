#include "Engine.h"

default_number_generator* pNumGenerator = nullptr;

void CEngine::Start(int ScreenWidth, int ScreenHeight, std::wstring NameApp)
{
	//инициализация движка
	pWindow = new Window();
	pWindow->ConstructWindow(ScreenWidth, ScreenHeight, NameApp);	//сборка окна консоли
	pTimer = new Timer();
	pMenu = new Menu();
	pNumGenerator = new default_number_generator();
	pNetwork = new Network();
	if (pWindow && pTimer && pMenu && pNumGenerator && pNetwork)		//если всё запущено, то устанавливаем флаг о том, что движок запущен
	{
		bIsRunning = true;
		GameThread();
	}	
}

void CEngine::Stop()
{
	delete pWindow;
	delete pTimer;
	delete pMenu;
	delete pNumGenerator;
	delete pNetwork;
}

void CEngine::GameThread()			//основное игровое ядро
{
	if (!OnUserCreate())
		bIsRunning = false;

	int fps = 0;
	double fpsTime = 0.0;
	while (bIsRunning)
	{
		pWindow->ClearAllWindow();
		pTimer->UpdateTimer();

		double deltaTime = pTimer->GetDeltaTimeSec();
		fpsTime += deltaTime;
		fps++;
		if (fpsTime >= 1.0)
		{
			fpsTime -= 1.0;
			pWindow->ChangeAppNme(L"FPS: " + std::to_wstring(fps) + L" FPS(instant): " + std::to_wstring(1.0f / deltaTime));
			fps = 0;
		}		

		if (!OnUserUpdate(deltaTime))
			bIsRunning = false;

		pWindow->UpdateWindow();
	}

	OnUserDestroy();
	Stop();
}
