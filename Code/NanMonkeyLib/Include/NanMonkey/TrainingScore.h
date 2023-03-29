#pragma once

#include "Dimention.h"

/*
want more data for each pixel to guide training
*/
namespace NanMonkey
{
	class Stage;

	class TrainingScore
	{
	public:
		class PixelData
		{
		public:
			PixelData();
			void AddSample(const float delta);
			const float GetAverage() const;
			const float GetScore() const;
		private:
			int m_sampleCount;
			float m_sumPositive;
			float m_sumNegative;
		};

		TrainingScore(const Dimention& dimention);

		void GatherScore(const Stage& target, const Stage& actualResult);
		const float GetDeltaScore();

		const Dimention& GetDimention() const { return m_dimention; }

	private:
		Dimention m_dimention;
		std::vector<PixelData> m_pixelDataArray;

		bool m_deltaScoreValid;
		float m_deltaScore;

	};
}