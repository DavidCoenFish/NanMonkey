#include "Stdafx.h"
#include "VisualCortex.h"
#include "UnitTest.h"

namespace
{
	const int CalculateNumberOfStepsNeeded(const int x, const int y, const int stride)
	{
		//steps = log(max(x,y)) / log(stride)
		//stride^steps = max(x,y)
		const int result = (int)(ceil(log(std::max(x,y)) / log(stride)));
	}
}

#if defined(UNITTEST)
const bool VisualCortex::UnitTest()
{
	UNIT_TEST_HEAD("VisualCortex");
	bool ok = true;

	if (ok)
	{
	}

	return ok;
}
#endif

std::vector<std::shared_ptr<Step>> VisualCortex::GenerateStepArrayVisualCortex(const int x, const int y, const int z, const int stride)
{
}
/*
input 16x16, stride 4
step 0:
16x16, all index are VisualCortex
step 1:
16x16, top 4x4 
step 2:
16x16, top 1x1 
*/
const bool VisualCortex::IsIndexVisualCortex(const int x, const int y, const int z, const int stride, const int indexX, const int indexY, const int indexZ, const int stepIndex)
{

}
