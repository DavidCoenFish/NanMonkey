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

			void ModifyWeight(const float delta);

			const float GetWeight() const { return m_weight; }
			const Index& GetIndex() const { return m_index; }

		private:
			float m_weight;
			Index m_index;
		};

	public:
		static std::shared_ptr<StepPixel> FactoryCopy(const StepPixel& stepPixel);

		StepPixel(const bool locked, const std::vector<Reference>& reference = std::vector<Reference>());

		const float EvaluePixel(const Dimention& dimention, const Stage& input) const;
		void MutateAdd(const Dimention& dimention, const Index& pixelIndex, Random& random, const float mutateEnergyNormalised);
		void Mutate(const Dimention& dimention, Random& random, const float mutateEnergyNormalised);

		void SetLocked(const bool locked){ m_locked = locked; }
		const bool GetLocked() const { return m_locked; }

		std::vector<Reference>& GetReferenceArray(){ return m_referenceArray;}


		//void ClearScore();
		//void AddScore(const float score);
		//const float GetScore() const;

	private:
		//flag for pixel being locked~ don't want to mutate "visual cortex"
		bool m_locked;
		std::vector<Reference> m_referenceArray;

		//float m_scoreSumPositive;
		//float m_scoreSumNegative;

	};
}