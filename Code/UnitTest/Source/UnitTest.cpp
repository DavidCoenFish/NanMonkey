#include "UnitTest.h"
#include <sstream>
#include <iostream>

void UnitTest::Report(const char* const pMessage, const char* const pFile, const char* const pFunc, const long line, const char* const pTime)
{
	std::ostringstream message;
	message << pMessage << " " << pFunc << " " << pTime << " " << pFile << ":" << line << std::endl;

	MESSAGE(message.str());
}


void UnitTest::ReportFail(const std::string& expected, const std::string& got, const char* const pFile, const char* const pFunc, const long line, const char* const pTime, const char* const pExpected)
{
	std::ostringstream message;
	message << "Fail: Got[" << got << "] " << pExpected << "[" << expected << "] " << " " << pFunc << " " << pTime << " " << pFile << ":" << line << std::endl;

	MESSAGE(message.str());
}
