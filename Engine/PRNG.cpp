#include"PRNG.h"

NumberGenerator* pNumGenerator = nullptr;

NumberGenerator::NumberGenerator()
{
	seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	RandomInit();
	pTimer->SetTimerMSec(Randomize(300000, 600000), [this]() {this->UpdateGenerator(); }, 1);	//созадть таймер в пределах от 5 до 10 минут, для обновления генератора
}

NumberGenerator::NumberGenerator(uint32_t minRange, uint32_t maxRange) :NumberGenerator()
{
	this->minRange = minRange;
	this->maxRange = maxRange;
}

void NumberGenerator::SetRange(uint32_t minRange, uint32_t maxRange)
{
	this->minRange = minRange;
	this->maxRange = maxRange;
}

uint32_t NumberGenerator::GetMin()
{
	return minRange;
}

uint32_t NumberGenerator::GetMax()
{
	return maxRange;
}

uint32_t NumberGenerator::Randomize()
{
	uint64_t y = 0;
	
	y = (m_mt[m_index] & MASK_UPPER) | (m_mt[(m_index + 1) % N] & MASK_LOWER);

	if (y & 1u)
		m_mt[m_index] = m_mt[(m_index + M) % N] ^ (y >> 1) ^ A;
	else
		m_mt[m_index] = m_mt[(m_index + M) % N] ^ (y >> 1) ^ 0;

	y = m_mt[m_index];
	y ^= (y >> U);
	y ^= (y << S) & B;
	y ^= (y << T) & C;
	y ^= (y >> L);

	y = y % ((uint64_t)maxRange - (uint64_t)minRange + (uint64_t)1) + (uint64_t)minRange;

	m_index = (m_index + 1) % N;

	if (y > maxRange)
		y = maxRange;
	if (minRange > maxRange)
		return 0;
	return (uint32_t)y;
}

uint32_t NumberGenerator::Randomize(uint32_t minRange, uint32_t maxRange)
{
	uint64_t y = 0;

	y = (m_mt[m_index] & MASK_UPPER) | (m_mt[(m_index + 1) % N] & MASK_LOWER);

	if (y & 1u)
		m_mt[m_index] = m_mt[(m_index + M) % N] ^ (y >> 1) ^ A;
	else
		m_mt[m_index] = m_mt[(m_index + M) % N] ^ (y >> 1) ^ 0;

	y = m_mt[m_index];
	y ^= (y >> U);
	y ^= (y << S) & B;
	y ^= (y << T) & C;
	y ^= (y >> L);

	y = y % ((uint64_t)maxRange - (uint64_t)minRange + (uint64_t)1) + (uint64_t)minRange;

	if (y > maxRange)
		y = maxRange;
	if (minRange > maxRange)
		return 0;
	return (uint32_t)y;
}

void NumberGenerator::UpdateGenerator()
{
	seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	RandomInit();
	pTimer->SetTimerMSec(Randomize(300000, 600000), [this]() {this->UpdateGenerator(); }, 1);	//созадть таймер в пределах от 5 до 10 минут, для обновления генератора
}

void NumberGenerator::RandomInit()
{
	m_mt[0] = seed;
	for (m_index = 1; m_index < N; m_index++)
		m_mt[m_index] = (1812433253U * (m_mt[m_index - 1] ^ (m_mt[m_index - 1] >> 30)) + m_index);
	m_index = 0;
}
