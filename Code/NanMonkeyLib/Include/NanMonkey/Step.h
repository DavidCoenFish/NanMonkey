#pragma once

#include "Dimention.h"

namespace NanMonkey
{
	class Stage;
	class StepPixel;

	class Step
	{
	public:
		static std::shared_ptr<Step> FactoryCopyStep(const Dimention& dimention); 

		Step(const Dimention& dimention, const std::vector<std::shared_ptr<StepPixel>>& data = std::vector<std::shared_ptr<StepPixel>>());

		std::shared_ptr<Stage> Perform(const Stage& input) const;

		//visit pixel? getPixel? tweak pixel 
		//void ClearScore();
		//const float GetScore();

	private:
		Dimention m_dimention;
		std::vector<std::shared_ptr<StepPixel>> m_data;
	};
}