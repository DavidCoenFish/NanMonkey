#include "Stdafx.h"
#include "TrainingData.h"
#include "TrainingInput.h"
#include "UnitTest.h"

#if defined(UNITTEST)
const bool TrainingData::UnitTest()
{
	UNIT_TEST_HEAD("TrainingData");

	bool ok = true;

	return ok;
}
#endif

std::shared_ptr<TrainingData> TrainingData::FactoryFile(const std::string& filePath)
{
	std::vector< std::shared_ptr< TrainingInput > > inputArray;



	return std::make_shared<TrainingData>(inputArray);
}

TrainingData::TrainingData(
	const std::vector< std::shared_ptr< TrainingInput > >& inputArray
	)
	: m_inputArray(inputArray)
{
	return;
}
