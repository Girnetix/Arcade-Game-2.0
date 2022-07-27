#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <list>
#include <Windows.h>
#include <functional>

class CTimerValue
{
	int64_t value = 0;
public:
	CTimerValue();
	CTimerValue(double seconds);
	CTimerValue(int64_t value);
	void Clear();

	CTimerValue& operator=(const CTimerValue& other);

	CTimerValue& operator+=(const CTimerValue& other);
	CTimerValue& operator+(const CTimerValue& other);

	CTimerValue& operator-=(const CTimerValue& other);
	CTimerValue& operator-(const CTimerValue& other);

	bool operator >(const CTimerValue& other);
	bool operator <(const CTimerValue& other);

	bool operator >=(const CTimerValue& other);
	bool operator <=(const CTimerValue& other);

	//�������� ����� � �������� ��� � ������������� (������������ ������ ��� ��������� �����������)
	double GetSeconds();
	int64_t GetMilliseconds();
};

class Timer
{
public:
	enum class TimerHandleState { Running, Paused, Finished };
public:
	Timer();
	~Timer();
	void UpdateTimer();															//���������� �������
	bool PauseTimer(unsigned int id);											//������������� ������
	bool UnpauseTimer(unsigned int id);											//����������� ������

	double TimeLeft(unsigned int id);											//���������� ����� ������ ������� (� �������)
	double GetDeltaTimeSec();													//���������� ������ ������� � ��������
	double GetDeltaTimeMSec();													//���������� ������ ������� � �������������

	uint32_t SetTimer(double seconds, double minutes, double hours, std::function<void()> lamdaFunction, int countOfRepeat = -1);
	uint32_t SetTimer(double seconds, std::function<void()> lamdaFunction, int countOfRepeat = -1);
	uint32_t SetTimerMSec(double milliseconds, std::function<void()> lamdaFunction, int countOfRepeat = -1);
	CTimerValue GetHighPrecisionTime();											//���������� ���-�� ������ ����������
	uint64_t GetFreqency();
private:
	class TimerHandle
	{
	public:
		TimerHandleState TimerState = TimerHandleState::Running;				//��������� ����������� �������
		std::function<void()> function;											//������� ������� ��� ��������� ������
		double delay = 0.0, currentTime = 0.0;									//�������� � ������� ����� ����������� �������
		unsigned int id = 0;													//�� ����������� �������
		static unsigned int counter;											//������� �������� (���. ��� ������������� ����������� �������)
		int countOfRepeat = -1;													//���-�� ������������ �������(-1 -- ����������� ���-��)
	public:
		TimerHandle(double time, std::function<void()> lambda, int countOfRepeat);
	};
private:
	uint64_t timeBefore = 0, timeNow = 0, frequency = 0;						//��������� ����� � ������� (����� �������� � �������)
	double deltaTime = 0.0;														//����� ����� ����� ���������� ������� (� ��������)
	double CPUSpeed = 0.0;														//�������� ���������� (� ��)
	std::list<TimerHandle*> timerList;											//������ ���������� �� ��� ����������� ��������
private:
	TimerHandle* GetTimerHandle(unsigned int id);								//�������� ���������� ������� �� ��
};

extern Timer* pTimer;

#endif
