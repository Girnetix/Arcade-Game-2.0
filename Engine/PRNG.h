#pragma once
#ifndef PRNG_H
#define PRNG_H

#include "Timer.h"
#include <chrono>

class NumberGenerator
{
public:
	NumberGenerator();
	NumberGenerator(uint32_t minRange, uint32_t maxRange);
	void SetRange(uint32_t minRange, uint32_t maxRange);
	uint32_t GetMin();
	uint32_t GetMax();
	uint32_t Randomize();
private:
	uint32_t minRange = 0, maxRange = 0;
	uint64_t seed;

	static const uint16_t N = 624;
	static const uint16_t W = 32;
	static const uint16_t R = 31;
	static const uint16_t M = 397;
	static const uint32_t A = 0x9908B0DF;
	static const uint16_t U = 11;
	static const uint16_t S = 7;
	static const uint16_t T = 15;
	static const uint16_t L = 18;
	static const uint32_t B = 0x9D2C5680;
	static const uint32_t C = 0xEFC60000;

	const uint64_t MASK_LOWER = (1ull << R) - 1;
	const uint64_t MASK_UPPER = (1ull << R);

	uint16_t m_index = 0;
	uint64_t m_mt[N];
private:
	uint32_t Randomize(uint32_t minRange, uint32_t maxRange);
	void UpdateGenerator();
	void RandomInit();
};

extern NumberGenerator* pNumGenerator;

#endif