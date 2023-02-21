#pragma once
#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include<string>

class Exception
{
public:
	Exception(const std::string& error) :lastErr(error) {};
	const char* what() { return lastErr.c_str(); }
	std::string whatStr() { return lastErr; }
private:
	std::string lastErr;
};

#endif