// ConsoleApplication00.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Stdafx.h"

#include "NanMonkey.h"
#include "Network.h"
#include "Random.h"
#include "State.h"
#include "Step.h"
#include "TrainingData.h"
#include "TrainingInput.h"
#include "VisualCortex.h"

#include "SDK/Nlohmann/json.hpp"

class JsonInput {
public:
	std::string type;
	int dimentions[3];
	std::string subPath;
};

class JsonOutput {
public:
	std::string type;
	std::map<std::string, float> data;
};

class JsonConfig {
public:
	JsonInput input;
	JsonOutput output;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonInput, type, dimentions, subPath);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonOutput, type, data);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonConfig, input, output);

#if defined(UNITTEST)
int main()
{
	bool ok = true;
	std::cout << "UnitTest" << std::endl;
	ok &= NanMonkey::UnitTest();
	ok &= Network::UnitTest();
	ok &= Random::UnitTest();
	ok &= State::UnitTest();
	ok &= Step::UnitTest();
	ok &= TrainingData::UnitTest();
	ok &= TrainingInput::UnitTest();
	ok &= VisualCortex::UnitTest();
	std::cout << (ok?"Pass":"Fail") << std::endl;
	return ok;
}
#else
//C:\development\NanMonkey\Prototype\ConsoleApplication00\Data\Test00\config.json
int main(const int argc, const char** argv)
{
	if (3 != argc)
	{
		std::cout << "Usage:" << argv[0] << " <file path to config.json> <output dir>\n";
	}
	else
	{
		std::cout << argv[1] << "\n";

		std::string configPath(argv[1]);
		std::ifstream jsonFile(configPath);
		nlohmann::json data = nlohmann::json::parse(jsonFile);

		auto config = data.get<JsonConfig>();

		auto pNetwork = Network::Factory(
			config.input.dimentions[0], 
			config.input.dimentions[1], 
			config.input.dimentions[2]
		);

		//load training data
		auto pTrainingData = TrainingData::FactoryImageGreyscale(
			configPath,
			config.input.subPath,
			config.input.dimentions[0], 
			config.input.dimentions[1], 
			config.input.dimentions[2],
			config.output.data
			);

		//train

		//save out network
	}

	return 0;
}

#endif
