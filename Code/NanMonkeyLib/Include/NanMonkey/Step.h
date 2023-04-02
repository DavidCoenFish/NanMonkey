#pragma once

#include "Dimention.h"

namespace NanMonkey
{
	class Stage;
	class StepPixel;

	class Step
	{
	public:
		static std::shared_ptr<Step> FactoryCopyStepWeight(const Dimention& dimention, const std::vector<float>& weight); 
		static std::shared_ptr<Step> FactoryCopyRandom(const Dimention& dimention, Random& random, const float mutateEnergyNormalised);
		static std::shared_ptr<Step> FactoryCopy(const Step& step); 

		Step(const Dimention& dimention, const std::vector<std::shared_ptr<StepPixel>>& data = std::vector<std::shared_ptr<StepPixel>>());

		const Dimention& GetDimention() const { return m_dimention; }

		std::shared_ptr<Stage> Perform(const Stage& input) const;

		std::shared_ptr<StepPixel> GetStepPixel(const int offset) const;

	private:
		Dimention m_dimention;
		std::vector<std::shared_ptr<StepPixel>> m_data;
	};
}