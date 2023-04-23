#include "Main.h"
#include "Dimention.h"
#include "Simple.h"
#include <iostream>

int main()
{
	bool ok = true;
	std::cout << "UnitTest" << std::endl;
	ok &= Dimention::UnitTest();
	//ok &= Simple::UnitTest();

	//ok &= NanMonkey::UnitTest();
	//ok &= Network::UnitTest();
	//ok &= Random::UnitTest();
	//ok &= State::UnitTest();
	//ok &= Step::UnitTest();
	//ok &= TrainingData::UnitTest();
	//ok &= TrainingInput::UnitTest();
	//ok &= VisualCortex::UnitTest();
	std::cout << (ok?"Pass":"Fail") << std::endl;
	return ok;
}
