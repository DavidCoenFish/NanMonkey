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
			Reference(const float weight, const Index& index);

			const float GetWeight() const { return m_weight; }
			const Index& GetIndex() const { return m_index; }

		private:
			float m_weight;
			Index m_index;
		};

	public:
		StepPixel(const std::vector<Reference>& reference = std::vector<Reference>());

		const float EvaluePixel(const Dimention& dimention, const Stage& input) const;

		//void ClearScore();
		//void AddScore(const float score);
		//const float GetScore() const;

	private:
		//flag for pixel being locked~ don't want to mutate "visual cortex"
		std::vector<Reference> m_referenceArray;

		//float m_scoreSumPositive;
		//float m_scoreSumNegative;

	};
}