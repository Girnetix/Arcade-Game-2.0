#include "Timer.h"

Timer* pTimer = nullptr;

unsigned int Timer::TimerHandle::counter = 0;

Timer::Timer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	uint64_t CPUBefore = 0, CPUAfter = 0;
	uint64_t timeAfter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&timeNow);
	timeBefore = timeNow;
	timeAfter = timeNow + frequency / 4;
	CPUBefore = __rdtsc();
	do
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&timeNow);
	} while (timeNow < timeAfter);
	CPUAfter = __rdtsc();
	CPUSpeed = floor((double)((CPUAfter - CPUBefore) * frequency / (timeNow - timeBefore)) / 1000000);
	CPUSpeed *= 1000000;
	timeBefore = timeNow;
}

Timer::~Timer()
{
	timerList.clear();
}

void Timer::UpdateTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&timeNow);
	deltaTime = (timeNow / 4.0 - timeBefore / 4.0) / (frequency / 4.0);			//получаем время между вызовами этого метода (в секундах)
	timeBefore = timeNow;
	for (auto iterator = timerList.begin(); iterator != timerList.end();)
	{
		TimerHandle* currentTimer = *iterator;
		switch (currentTimer->TimerState)
		{
			case TimerHandleState::Running:										//если таймер запущен
				currentTimer->currentTime += deltaTime;							//увеличиваем время работы таймера на время между вызовами метода
				if (currentTimer->currentTime >= currentTimer->delay)			//если время работы превышает время задержки, то...
				{
					currentTimer->function();									//вызываем функцию
					currentTimer->currentTime -= currentTimer->delay;			//уменьшаем время работы на нашу задержку
					if (currentTimer->countOfRepeat > 0)
						currentTimer->countOfRepeat--;							//уменьшаем кол-во срабатываний
					if (currentTimer->countOfRepeat == 0)
						currentTimer->TimerState = TimerHandleState::Finished;	//устанавливаем флаг, что таймер завершил свою работу
				}
				iterator++; 
				break;
			case TimerHandleState::Paused:	 iterator++; break;					//если таймер приостановлен, то переходим к следующему таймеру
			case TimerHandleState::Finished: iterator = timerList.erase(iterator); break;	//если таймер завершил свою работу, то удаляем его
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

CTimerValue Timer::GetHighPrecisionTime()
{
	int64_t ticks = __rdtsc();
	return ticks;
}

uint64_t Timer::GetFrequency()
{
	return CPUSpeed;
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

CTimerValue::CTimerValue()
{
	value = 0;
}

CTimerValue::CTimerValue(double seconds)
{
	value = (int64_t)(seconds*pTimer->GetFrequency());
}

CTimerValue::CTimerValue(int64_t value)
{
	this->value = value;
}

void CTimerValue::Clear()
{
	value = 0;
}

CTimerValue& CTimerValue::operator=(const CTimerValue& other)
{
	value = other.value;
	return *this;
}

CTimerValue& CTimerValue::operator+=(const CTimerValue& other)
{
	value += other.value;
	return *this;
}

CTimerValue& CTimerValue::operator+(const CTimerValue& other)
{
	return CTimerValue(*this)+=other;
}

CTimerValue& CTimerValue::operator-=(const CTimerValue& other)
{
	value -= other.value;
	return *this;
}

CTimerValue& CTimerValue::operator-(const CTimerValue& other)
{
	return CTimerValue(*this) -= other;
}

bool CTimerValue::operator>(const CTimerValue& other)
{
	return value > other.value;
}

bool CTimerValue::operator<(const CTimerValue& other)
{
	return value < other.value;
}

bool CTimerValue::operator>=(const CTimerValue& other)
{
	return value >= other.value;;
}

bool CTimerValue::operator<=(const CTimerValue& other)
{
	return value <= other.value;
}

bool CTimerValue::operator==(const CTimerValue& other)
{
	return value == other.value;
}

double CTimerValue::GetSeconds()
{
	return value / pTimer->GetFrequency();
}

int64_t CTimerValue::GetMilliseconds()
{
	return GetSeconds() * 1000;
}
