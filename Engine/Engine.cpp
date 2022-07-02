#include "Engine.h"

void CEngine::Start(int ScreenWidth, int ScreenHeight, std::wstring NameApp)
{
	//������������� ������
	pWindow = new Window();
	pWindow->ConstructWindow(ScreenWidth, ScreenHeight, NameApp);	//������ ���� �������
	pTimer = new Timer();
	pMenu = new Menu();
	pFile = new FileSystem();
	pNumGenerator = new NumberGenerator();
	if (pWindow && pTimer && pMenu && pFile && pNumGenerator)		//���� �� ��������, �� ������������� ���� � ���, ��� ������ �������
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

void CEngine::GameThread()			//�������� ������� ����
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
