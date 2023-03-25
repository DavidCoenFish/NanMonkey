class Step;
class State;

namespace VisualCortex
{
#if defined(UNITTEST)
	const bool UnitTest();
#endif
	std::vector<std::shared_ptr<Step>> GenerateStepArrayVisualCortex(const int x, const int y, const int z, const int stride);
	const bool IsIndexVisualCortex(const int x, const int y, const int z, const int stride, const int indexX, const int indexY, const int indexZ, const int stepIndex);

};