#include "Stdafx.h"
#include "TrainingData.h"
#include "TrainingInput.h"
#include "UnitTest.h"
#include "State.h"

#include "SDK/Nlohmann/json.hpp"

#if defined(UNITTEST)
const bool TrainingData::UnitTest()
{
	UNIT_TEST_HEAD("TrainingData");

	bool ok = true;

	return ok;
}
#endif

namespace
{
	void VisitFolder(
		std::vector< std::shared_ptr< TrainingInput > >& inputArray,
		const std::filesystem::path& folderPath,
		const int x, 
		const int y, 
		const int z, 
		const std::map< std::string, float> baseTargetMap
	)
	{
		//is there a tag json
		std::map< std::string, float> targetMap(baseTargetMap);
		std::ifstream jsonFile(folderPath / "tag.json");
		if (jsonFile.good())
		{
			nlohmann::json data = nlohmann::json::parse(jsonFile);
			if (data.is_object())
			{
				//data.to
				auto pObject = data.get< nlohmann::json::object_t >();
				for (auto key : pObject)
				{
					targetMap[key.first] = key.second;
				}
			}
		}

		auto pTarget = State::Factory(x, y, z, State::TagMapToData(x, y, z, targetMap));

		//load images if found
		//recurse to children folders
		for (const auto & entry : std::filesystem::directory_iterator(folderPath))
		{
			auto path = folderPath / entry;
			if (std::filesystem::is_directory(path))
			{
				VisitFolder(inputArray, folderPath / entry, x, y, z, targetMap);
			}
			else
			{
				if (".png" == path.extension())
				{
					auto data = State::PngGreyscaleToData(x, y, z, path.string());
					auto pInput = State::Factory(x, y, z, data);

					inputArray.push_back(std::make_shared<TrainingInput>(pInput, pTarget));
				}
			}
		}
	}

};

std::shared_ptr<TrainingData> TrainingData::FactoryImageGreyscale(
	const std::string& configPath,
	const std::string& subPath,
	const int x, 
	const int y, 
	const int z, 
	const std::map< std::string, float> baseTargetMap
	)
{
	std::vector< std::shared_ptr< TrainingInput > > inputArray;

	//Input
	std::filesystem::path inputPath(configPath);
	inputPath.remove_filename();
	inputPath /= subPath;

	VisitFolder(inputArray, inputPath, x, y, z, baseTargetMap);

	return std::make_shared<TrainingData>(inputArray);
}



TrainingData::TrainingData(
	const std::vector< std::shared_ptr< TrainingInput > >& inputArray
	)
	: m_inputArray(inputArray)
{
	return;
}
