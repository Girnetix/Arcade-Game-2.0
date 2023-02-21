#include<Engine/Engine.h>

#include<Engine/Server.h>
#include<Engine/Client.h>

#include<iostream>
#include<chrono>

CServer server;
CClient client;


class net :public CEngine
{
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(double deltaTime) override;
	void OnUserDestroy() override;
	int sec = 0, min = 0, hour = 0;
	uint32_t id = 0;
};

bool net::OnUserCreate()
{
	id = pTimer->SetTimer(1.0, [&]() {
		sec++;
		min = sec / 60;
		hour = min / 60;
		});
	pTimer->SleepTimerHandle(id, 10.0);
	return true;
}

bool net::OnUserUpdate(double deltaTime)
{
	pWindow->PrintMsg(0, 0, std::to_wstring(pTimer->GetWorkingTime()));
	wchar_t msg[20];
	swprintf_s(msg, 20, L"%02d:%02d:%02d", hour, min % 60, sec % 60);
	pWindow->PrintMsg(0, 1, msg, FG_CYAN);
	pTimer->PrintInfo();
	return true;
}

void net::OnUserDestroy()
{
	pNetwork->Shutdown();
}


int main()
{
	net game;
	game.Start(120, 50, L"Test");
	return 0;
}