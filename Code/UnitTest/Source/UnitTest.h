#pragma once

#include <string>

#define UNIT_TEST_HEAD(MESSAGE) UnitTest::Report(MESSAGE, __FILE__, __func__, __LINE__, __TIME__)
#define UNIT_TEST_COMPARE(EXPECTED, GOT) UnitTest::Compare(EXPECTED, GOT, __FILE__, __func__, __LINE__, __TIME__)
#define UNIT_TEST_NOT_COMPARE(NOT_EXPECTED, GOT) UnitTest::NotCompare(NOT_EXPECTED, GOT, __FILE__, __func__, __LINE__, __TIME__)
#define UNIT_TEST_NOT_NULL(POINTER) UnitTest::NotNull(POINTER, __FILE__, __func__, __LINE__, __TIME__)
#define MESSAGE(MESSAGE) std::cout << MESSAGE << std::endl;

namespace UnitTest
{
	void Report(const char* const pMessage, const char* const pFile, const char* const pFunc, const long line, const char* const pTime);
	void ReportFail(const std::string& expected, const std::string& got, const char* const pFile, const char* const pFunc, const long line, const char* const pTime, const char* const pExpected);

	template< typename TYPE>
	const bool Compare(const TYPE expected, const TYPE got, const char* const pFile, const char* const pFunc, const long line, const char* const pTime)
	{
		if (expected == got)
		{
			return true;
		}

		ReportFail(std::to_string(expected), std::to_string(got), pFile, pFunc, line, pTime, "expected");

		return false;
	}

	template< typename TYPE>
	const bool NotCompare(const TYPE notExpected, const TYPE got, const char* const pFile, const char* const pFunc, const long line, const char* const pTime)
	{
		if (notExpected != got)
		{
			return true;
		}

		ReportFail(std::to_string(notExpected), std::to_string(got), pFile, pFunc, line, pTime, "not expected");

		return false;
	}

	template< typename TYPE>
	const bool NotNull(const TYPE* const pPointer, const char* const pFile, const char* const pFunc, const long line, const char* const pTime)
	{
		if (nullptr != pPointer)
		{
			return true;
		}

		ReportFail("nullptr", std::to_string((long long)pPointer), pFile, pFunc, line, pTime, "not null");

		return false;
	}

};