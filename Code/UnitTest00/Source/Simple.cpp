#include "Simple.h"

#include "Main.h"
#include "UnitTest.h"

#include "NanMonkey/Dimention.h"
#include "NanMonkey/TrainingData.h"


const bool Simple::UnitTest()
{
	UNIT_TEST_HEAD("Simple");
	bool ok = true;

	if (ok)
	{
		auto pTrainingData = NanMonkey::TrainingData::Factory(
			NanMonkey::Dimention({2,2}),
			NanMonkey::Dimention({4}), //solid, horizontal, vertical, diagonal
			{ 
				{ { 0.0f,0.0f, 0.0f,0.0f }, { 1.0f,0.0f,0.0f,0.0f } },
				{ { 1.0f,0.0f, 0.0f,0.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 0.0f,1.0f, 0.0f,0.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 1.0f,1.0f, 0.0f,0.0f }, { 0.0f,1.0f,0.0f,0.0f } },
				{ { 0.0f,0.0f, 1.0f,0.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 1.0f,0.0f, 1.0f,0.0f }, { 0.0f,0.0f,1.0f,0.0f } },
				{ { 0.0f,1.0f, 1.0f,0.0f }, { 0.0f,0.0f,0.0f,1.0f } },
				{ { 1.0f,1.0f, 1.0f,0.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 0.0f,0.0f, 0.0f,1.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 1.0f,0.0f, 0.0f,1.0f }, { 0.0f,0.0f,0.0f,1.0f } },
				{ { 0.0f,1.0f, 0.0f,1.0f }, { 0.0f,0.0f,1.0f,0.0f } },
				{ { 1.0f,1.0f, 0.0f,1.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 0.0f,0.0f, 1.0f,1.0f }, { 0.0f,1.0f,0.0f,0.0f } },
				{ { 1.0f,0.0f, 1.0f,1.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 0.0f,1.0f, 1.0f,1.0f }, { 0.0f,0.0f,0.0f,0.0f } },
				{ { 1.0f,1.0f, 1.0f,1.0f }, { 1.0f,0.0f,0.0f,0.0f } } 
			}
		);

		//auto pNeuralNetwork = Train::TrainNetwork(*pTrainingData, (const std::string& output){
		//	MESSAGE(output);
		//});

	}

	return ok;
}
