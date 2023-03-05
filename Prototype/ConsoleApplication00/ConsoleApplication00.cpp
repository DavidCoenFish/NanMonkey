// ConsoleApplication00.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Stdafx.h"

#include "Network.h"
#include "Random.h"
#include "State.h"
#include "Step.h"

#include "SDK/Nlohmann/json.hpp"

class JsonInput {
public:
	std::string type;
	int dimentions[3];
};

class JsonOutput {
public:
	std::string type;
	std::vector<std::string> data;
};

class JsonConfig {
public:
	JsonInput input;
	JsonOutput output;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonInput, type, dimentions);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonOutput, type, data);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonConfig, input, output);

#if defined(UNITTEST)
int main()
{
	bool ok = true;
	std::cout << "UnitTest" << std::endl;
	ok &= Network::UnitTest();
	ok &= Random::UnitTest();
	ok &= State::UnitTest();
	ok &= Step::UnitTest();
	std::cout << (ok?"Pass":"Fail") << std::endl;
	return ok;
}
#else
int main(const int argc, const char** argv)
{
	if (3 != argc)
	{
		std::cout << "Usage:" << argv[0] << " <file path to config.json> <output dir>\n";
	}
	else
	{
		std::cout << argv[1] << "\n";

		std::ifstream jsonFile(argv[1]);
		nlohmann::json data = nlohmann::json::parse(jsonFile);

		auto config = data.get<JsonConfig>();

		auto pNetwork = Network::Factory(
			config.input.dimentions[0], 
			config.input.dimentions[1], 
			config.input.dimentions[2],
			0, 2, 0.1f, 0.1f
		);

		//load training data

		//train

		//save out network
	}

	return 0;
}

#endif
