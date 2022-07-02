#include "Engine.h"

void CEngine::Start(int ScreenWidth, int ScreenHeight, std::wstring NameApp)
{
	//инициализация движка
	pWindow = new Window();
	pWindow->ConstructWindow(ScreenWidth, ScreenHeight, NameApp);	//сборка окна консоли
	pTimer = new Timer();
	pMenu = new Menu();
	pFile = new FileSystem();
	pNumGenerator = new NumberGenerator();
	if (pWindow && pTimer && pMenu && pFile && pNumGenerator)		//если всё запущено, то устанавливаем флаг о том, что движок запущен
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
	delete pFile;
	delete pNumGenerator;
}

void CEngine::GameThread()			//основное игровое ядро
{
	if (!OnUserCreate())
		bIsRunning = false;

	while (bIsRunning)
	{
		pTimer->UpdateTimer();

		double deltaTime = pTimer->GetDeltaTimeSec();
		pWindow->ChangeAppNme(L"FPS: " + std::to_wstring(1.0 / deltaTime));

		if (!OnUserUpdate(deltaTime))
			bIsRunning = false;

		pWindow->UpdateWindow();
	}

	OnUserDestroy();
	Stop();
}
