#include "Stdafx.h"
#include "TrainingInput.h"
#include "State.h"
#include "UnitTest.h"

#if defined(UNITTEST)
const bool TrainingInput::UnitTest()
{
	UNIT_TEST_HEAD("TrainingInput");

	bool ok = true;

	return ok;
}
#endif

TrainingInput::TrainingInput(
	const std::shared_ptr< State >& input,
	const std::shared_ptr< State >& target
	)
	: m_input(input)
	, m_target(target)
{
	return;
}

