#pragma once

#include "Index.h"

namespace NanMonkey
{
	class Dimention;
	class Stage;

	class StepPixel
	{
	public:
		class Reference
		{
		public:
			const float GetWeight() const { return m_weight; }
			const Index& GetIndex() const { return m_index; }

		private:
			float m_weight;
			Index m_index;
		};

	public:
		StepPixel(const std::vector<Reference>& reference = std::vector<Reference>());

		const float EvaluePixel(const Dimention& dimention, const Stage& input) const;

	private:
		std::vector<Reference> m_referenceArray;
	};
}