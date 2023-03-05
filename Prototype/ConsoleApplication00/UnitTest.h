
#define UNIT_TEST_HEAD(MESSAGE) UnitTest::Report(MESSAGE, __FILE__, __func__, __LINE__, __TIME__)
#define UNIT_TEST_COMPARE(EXPECTED, GOT) UnitTest::Compare(EXPECTED, GOT, __FILE__, __func__, __LINE__, __TIME__)

namespace UnitTest
{
	void Report(const char* const pMessage, const char* const pFile, const char* const pFunc, const long line, const char* const pTime);
	void ReportFail(const std::string& expected, const std::string& got, const char* const pFile, const char* const pFunc, const long line, const char* const pTime);

	template< typename TYPE>
	const bool Compare(const TYPE expected, const TYPE got, const char* const pFile, const char* const pFunc, const long line, const char* const pTime)
	{
		if (expected == got)
		{
			return true;
		}

		ReportFail(std::to_string(expected), std::to_string(got), pFile, pFunc, line, pTime);

		return false;
	}

};