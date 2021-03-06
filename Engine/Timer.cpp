#include"Timer.h"

Timer* pTimer = nullptr;

unsigned int Timer::TimerHandle::counter = 0;

Timer::Timer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	uint64_t CPUBefore = 0, CPUAfter = 0;
	uint64_t timeAfter = 0;
	double CPUSpeed = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&timeNow);
	timeBefore = timeNow;
	timeAfter = timeNow + frequency / 4;
	CPUBefore = __rdtsc();
	do
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&timeNow);
	} while (timeNow < timeAfter);
	CPUAfter = __rdtsc();
	CPUSpeed = floor((double)((CPUAfter - CPUBefore) * frequency / (timeNow - timeBefore)) / 1000000.0) / 1000.0;
	timeBefore = timeNow;
}

Timer::~Timer()
{
	timerList.clear();
}

void Timer::UpdateTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&timeNow);
	deltaTime = (timeNow / 4.0 - timeBefore / 4.0) / (frequency / 4.0);			//???????? ????? ????? ???????? ????? ?????? (? ????????)
	timeBefore = timeNow;
	for (auto iterator = timerList.begin(); iterator != timerList.end();)
	{
		TimerHandle* currentTimer = *iterator;
		switch (currentTimer->TimerState)
		{
			case TimerHandleState::Running:										//???? ?????? ???????
				currentTimer->currentTime += deltaTime;							//??????????? ????? ?????? ??????? ?? ????? ????? ???????? ??????
				if (currentTimer->currentTime >= currentTimer->delay)			//???? ????? ?????? ????????? ????? ????????, ??...
				{
					currentTimer->function();									//???????? ???????
					currentTimer->currentTime -= currentTimer->delay;			//????????? ????? ?????? ?? ???? ????????
					if (currentTimer->countOfRepeat > 0)
						currentTimer->countOfRepeat--;							//????????? ???-?? ????????????
					if (currentTimer->countOfRepeat == 0)
						currentTimer->TimerState = TimerHandleState::Finished;	//????????????? ????, ??? ?????? ???????? ???? ??????
				}
				iterator++; 
				break;
			case TimerHandleState::Paused:	 iterator++; break;					//???? ?????? ?????????????, ?? ????????? ? ?????????? ???????
			case TimerHandleState::Finished: iterator = timerList.erase(iterator); break;	//???? ?????? ???????? ???? ??????, ?? ??????? ???
		}
	}
}

bool Timer::PauseTimer(unsigned int id)
{
	TimerHandle* currentTimer = GetTimerHandle(id);
	if (currentTimer != nullptr)
	{
		currentTimer->TimerState = TimerHandleState::Paused;
		return true;
	}
	else
		return false;
}

bool Timer::UnpauseTimer(unsigned int id)
{
	TimerHandle* currentTimer = GetTimerHandle(id);
	if (currentTimer != nullptr)
	{
		currentTimer->TimerState = TimerHandleState::Running;
		return true;
	}
	else
		return false;
}

double Timer::TimeLeft(unsigned int id)
{
	TimerHandle* currentTimer = GetTimerHandle(id);
	if (currentTimer != nullptr)
		return currentTimer->delay - currentTimer->currentTime;
	else
		return 0.0;
}

double Timer::GetDeltaTimeSec()
{
	return deltaTime;
}

double Timer::GetDeltaTimeMSec()
{
	return deltaTime * 1000.0;
}

uint32_t Timer::SetTimer(double seconds, double minutes, double hours, std::function<void()> lamdaFunction, int countOfRepeat)
{
	timerList.push_back(new TimerHandle(seconds + minutes * 60.0 + hours * 3600.0, lamdaFunction, countOfRepeat));
	return TimerHandle::counter;
}

uint32_t Timer::SetTimer(double seconds, std::function<void()> lamdaFunction, int countOfRepeat)
{
	timerList.push_back(new TimerHandle(seconds, lamdaFunction, countOfRepeat));
	return TimerHandle::counter;
}

uint32_t Timer::SetTimerMSec(double milliseconds, std::function<void()> lamdaFunction, int countOfRepeat)
{
	timerList.push_back(new TimerHandle(milliseconds / 1000.0, lamdaFunction, countOfRepeat));
	return TimerHandle::counter;
}

Timer::TimerHandle* Timer::GetTimerHandle(unsigned int id)
{
	for (auto iterator = timerList.begin(); iterator != timerList.end(); iterator++)
	{
		TimerHandle* currentTimer = *iterator;
		if (currentTimer->id == id)
			return currentTimer;
	}
	return nullptr;
}

Timer::TimerHandle::TimerHandle(double time, std::function<void()> lambda, int countOfRepeat)
{
	delay = time;
	function = lambda;
	this->countOfRepeat = countOfRepeat;
	id = counter;
	counter++;
}

